#ifndef BOOSTBEAST_ECHOSERVER_FAIL_H
#define BOOSTBEAST_ECHOSERVER_FAIL_H

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

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

void fail(beast::error_code ec, char const* what);


#endif //BOOSTBEAST_ECHOSERVER_FAIL_H
