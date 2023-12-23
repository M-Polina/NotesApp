//
// Created by Andrey Marusin on 23.12.2023.
//

#include "session.h"

session::session(tcp::socket&& socket)
            : ws_(std::move(socket))
{
}

void
session::run()
{
    // Set suggested timeout settings for the websocket
    ws_.set_option(
            websocket::stream_base::timeout::suggested(
                    beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
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
session::on_accept(beast::error_code ec)
{
    if(ec)
        return fail(ec, "accept");

    do_read();
}

void
session::do_read()
{
    ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                    &session::on_read,
                    shared_from_this()));
}

void
session::on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
{
    std::cout << "Got: " << beast::make_printable(buffer_.data()) << std::endl;
    std::cout <<"gi: "<< beast::buffers_to_string(buffer_.data()) <<std::endl;
    boost::ignore_unused(bytes_transferred);

    if(ec == websocket::error::closed)
        return;

//    if (beast::buffers_to_string(buffer_.data()) == "stop") {
//        std::cout << "stopped" << std::endl;
//        return;
//    }

    if(ec)
        fail(ec, "read");

    std::string message = beast::buffers_to_string(buffer_.data());
//    std::size_t messageSize = message.size();
    json request_json;
    try {
        request_json = JsonParser::stringToJson(message);
    } catch (std::exception ex){
        std::cerr << ex.what();
        return;
    }

    std::string request_type = request_json.at("type");

    if (request_json == LOGIN_TYPE) {
        std::string username = JsonParser::parseLoginJson(request_json);
    } else if (request_json == NOTES_TYPE) {
        std::vector<Note> got_notes = JsonParser::parseNotesJson(request_json);
    } else {
        std::cout << "wrong request type" << std::endl;
        return;
    }

    boost::beast::flat_buffer buf;
    boost::beast::ostream(buf) << beast::buffers_to_string(buffer_.data()) + " - from server";


//    std::string login_json_string = JsonParser::createLoginJsonString("hello");
//    std::string username = JsonParser::parseLoginJson(json::parse(login_json_string));
//    std::cout << username << std::endl;

    std::vector<Note> *notes = new std::vector<Note>();
    Note note("header", "text", "time");
    notes->push_back(note);
    Note note2("header2", "text2", "time2");
    notes->push_back(note2);

    std::string jsonNotes = JsonParser::createNotesJsonString(*notes);
    auto parsedNotes = JsonParser::parseNotesJson(json::parse(jsonNotes));

//    auto parsed_json = JsonParser::stringToJson(jsonNotes);


    ws_.text(ws_.got_text());
    ws_.async_write(
            buf.data(),
            beast::bind_front_handler(
                    &session::on_write,
                    shared_from_this()));
}

void
session::on_write(
        beast::error_code ec,
        std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    buffer_.consume(buffer_.size());

    do_read();
}

