#include <iostream>
#include <array>
#include <ostream>
#include <cmath>
#include <gtest/gtest.h>
//#include "ServerAlgorythms.h"
#include "JsonParser.h"
//#include "JsonParser.cpp"

TEST(NotesServer_Tests, test_1) {
//    bool is_valid = ServerAlgorythms::isNameValid("hello");
    std::string str_err = "New error";
    std::string str = JsonParser::createErrorJsonString(str_err);
//    std::cout << str << std::endl;
    ASSERT_EQ(true, true);
}
