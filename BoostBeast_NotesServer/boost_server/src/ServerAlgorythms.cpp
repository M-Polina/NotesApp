#include "ServerAlgorythms.hpp"

ServerAlgorythms::ServerAlgorythms() {}
#include <iostream>
bool ServerAlgorythms::isNameValid(std::string name)
{
    if (name.size() > 50 || name.size() < 3)
        return false;

    return true;
}
