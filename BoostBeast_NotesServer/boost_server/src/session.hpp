#pragma once
#ifndef BOOSTBEAST_ECHOSERVER_SESSION_H
#define BOOSTBEAST_ECHOSERVER_SESSION_H

#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "fail.hpp"
#include "JsonParser.hpp"
#include "Account.hpp"
#include "ServerAlgorythms.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;

public:
    explicit
    session(tcp::socket &&socket, std::shared_ptr<Account> accounts,
            std::shared_ptr<std::vector<std::string>> online_users);

    void
    run();

    void
    on_accept(beast::error_code ec);

    void
    do_read();

    void
    on_read(
            beast::error_code ec,
            std::size_t bytes_transferred);

    void
    on_write(
            beast::error_code ec,
            std::size_t bytes_transferred);

    void send_to_client(
            beast::error_code ec,
            std::size_t bytes_transferred);

    void send_message(std::string message);

public:
    std::shared_ptr<Account> accounts_;
    std::shared_ptr<std::vector<std::string>> onlineUsers_;
    std::string username_;

};


#endif //BOOSTBEAST_ECHOSERVER_SESSION_H
