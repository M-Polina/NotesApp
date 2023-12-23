//
// Created by Andrey Marusin on 23.12.2023.
//

#include "fail.h"
void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}