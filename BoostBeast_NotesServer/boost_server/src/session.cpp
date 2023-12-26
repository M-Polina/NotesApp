#include "session.hpp"

session::session(tcp::socket &&socket,
                 std::shared_ptr<Account> accounts,
                 std::shared_ptr<std::vector<std::string>> online_users)
        : ws_(std::move(socket)) {
    accounts_ = accounts;
    onlineUsers_ = online_users;
}

void
session::run() {
    // Set suggested timeout settings for the websocket
    ws_.set_option(
            websocket::stream_base::timeout::suggested(
                    beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type &res) {
                res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-async-ssl");
            }));

    // Accept the websocket handshake
    ws_.async_accept(
            beast::bind_front_handler(
                    &session::on_accept,
                    shared_from_this()));
}

void
session::on_accept(beast::error_code ec) {
    if (ec)
        return fail(ec, "accept");

    do_read();
}

void
session::do_read() {
    ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                    &session::on_read,
                    shared_from_this()));
}

void
session::on_read(
        beast::error_code ec,
        std::size_t bytes_transferred) {
//    std::cout << "Got: " << beast::make_printable(buffer_.data()) << std::endl;
//    std::cout << "gi: " << beast::buffers_to_string(buffer_.data()) << std::endl;
    boost::ignore_unused(bytes_transferred);

    if (ec == websocket::error::closed) {
        std::cout << "socket closed" << std::endl;
        auto iterator = std::find(onlineUsers_->begin(), onlineUsers_->end(), username_);
        if (iterator != onlineUsers_->cend()) {
            onlineUsers_->erase(iterator, iterator + 1);
        }

        return;
    }

    if (ec)
        fail(ec, "read");

    std::string message = beast::buffers_to_string(buffer_.data());

    json request_json;
    try {
        request_json = JsonParser::stringToJson(message);
    } catch (std::exception ex) {
        send_message(JsonParser::createErrorJsonString("Not a json request."));

        auto iterator = std::find(onlineUsers_->begin(), onlineUsers_->end(), username_);
        if (iterator != onlineUsers_->cend()) {
            onlineUsers_->erase(iterator, iterator + 1);
        }

        std::cerr << ex.what();
        return;
    }

    std::string request_type = request_json.at("type");

//    boost::beast::flat_buffer buf;
    buffer_.consume(buffer_.size());

    if (request_type == LOGIN_TYPE) {
        std::string username = JsonParser::parseLoginJson(request_json);
        if (ServerAlgorythms::isNameValid(username) == false) {
            std::cout << "invalid username" << std::endl;
            send_message(JsonParser::createErrorJsonString("Invalid username. Should be >=3, <=50."));
            return;
        } else {
            auto iterator = std::find(onlineUsers_->begin(), onlineUsers_->end(), username);
            if (iterator != onlineUsers_->cend()) {
                std::cout << "already online username" << std::endl;
                send_message(JsonParser::createErrorJsonString("This user is already online."));
                return;
            }
            onlineUsers_->push_back(username);
            std::shared_ptr<std::vector<Note>> notesList = accounts_->addAccount(username);
            username_ = username;
            std::string acc_notes = JsonParser::createNotesJsonString(*notesList);

            boost::beast::ostream(buffer_) << acc_notes;
            ws_.text(ws_.got_text());
            ws_.async_write(
                    buffer_.data(),
                    beast::bind_front_handler(
                            &session::on_write,
                            shared_from_this()));
        }
    } else if (request_type == NOTES_TYPE) {
        std::vector<Note> got_notes = JsonParser::parseNotesJson(request_json);
        for (Note note: got_notes) {
            accounts_->addNoteToAccount(username_, note);
        }
        buffer_.consume(buffer_.size());

        do_read();

    } else {
        std::cout << "Wrong request type" << std::endl;
        send_message(JsonParser::createErrorJsonString("Wrong json request type."));
        buffer_.consume(buffer_.size());
        do_read();
    }
}

void
session::on_write(
        beast::error_code ec,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");

    buffer_.consume(buffer_.size());

    do_read();
}

void session::send_message(std::string message) {
    buffer_.consume(buffer_.size());
    boost::beast::ostream(buffer_) << message;
    ws_.text(ws_.got_text());
    ws_.async_write(
            buffer_.data(),
            beast::bind_front_handler(
                    &session::send_to_client,
                    shared_from_this()));
}

void session::send_to_client(
        beast::error_code ec,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "send_to_client");

    buffer_.consume(buffer_.size());
}