#include "serveralgotythms.h"

ServerAlgotythms::ServerAlgotythms() {}

bool ServerAlgotythms::isNameValid(std::string name)
{
    if (name.size() > 50 || name.size() < 3)
        return false;

    return true;
}
