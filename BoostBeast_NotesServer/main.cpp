#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <memory>

#include "network/listener.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


int main(int argc, char* argv[])
{
    auto const port = static_cast<unsigned short>(std::atoi("8080"));

    net::io_context ioc;

    auto accounts = std::make_shared<Account>();
    auto online_users = std::make_shared<std::vector<std::string>>();

    std::make_shared<listener>(ioc, tcp::endpoint{tcp::v4(), port}, accounts, online_users)->run();

    ioc.run();

    return EXIT_SUCCESS;
}
