//
// Created by Andrey Marusin on 23.12.2023.
//

#ifndef BOOSTBEAST_ECHOSERVER_LISTENER_H
#define BOOSTBEAST_ECHOSERVER_LISTENER_H

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

#include "fail.h"
#include "session.h"


namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class listener : public std::enable_shared_from_this<listener> {
        net::io_context& ioc_;
        tcp::acceptor acceptor_;

    public:
        listener(net::io_context& ioc, tcp::endpoint endpoint);

        void run();

    private:
        void do_accept();

        void on_accept(beast::error_code ec, tcp::socket socket);
};


#endif //BOOSTBEAST_ECHOSERVER_LISTENER_H
