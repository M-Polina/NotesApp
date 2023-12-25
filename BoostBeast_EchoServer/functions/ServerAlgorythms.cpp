#include "ServerAlgorythms.h"

ServerAlgorythms::ServerAlgorythms() {}
#include <iostream>
bool ServerAlgorythms::isNameValid(std::string name)
{
    std::cout << name << std::endl;
    if (name.size() > 50 || name.size() < 3)
        return false;

    return true;
}
