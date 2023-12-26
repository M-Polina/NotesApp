#include <gtest/gtest.h>
#include "src/ServerAlgorythms.hpp"

TEST(ServerAlgorythmsTest, IsNameValid_NameLessThen_3)
{
    std::string name1 = "R";
    std::string name2 = "Lu";
    std::string name3 = "lui";
    std::string name4 = "luis";

    ASSERT_FALSE(ServerAlgorythms::isNameValid(name1));
    ASSERT_FALSE(ServerAlgorythms::isNameValid(name2));
    ASSERT_TRUE(ServerAlgorythms::isNameValid(name3));
    ASSERT_TRUE(ServerAlgorythms::isNameValid(name4));
}

TEST(ServerAlgorythmsTest, IsNameValid_NameGraterThen_50)
{
    std::string name1 = "1234567890asdfghjklzxcvbnderidjsjdjfkdlskdkfjcndkw52";
    std::string name2 = "1234567890asdfghjklzxcvbnderidjsjdjfkdlskdkfjcndk51";
    std::string name3 = "1234567890asdfghjklzxcvbnderidjsjdjfkdlskdkfjcnd50";
    std::string name4 = "1234567890asdfghjklzxcvbnderidjsjdjfkdlskdkfjcn49";

    ASSERT_FALSE(ServerAlgorythms::isNameValid(name1));
    ASSERT_FALSE(ServerAlgorythms::isNameValid(name2));
    ASSERT_TRUE(ServerAlgorythms::isNameValid(name3));
    ASSERT_TRUE(ServerAlgorythms::isNameValid(name4));
}

TEST(ServerAlgorythmsTest, IsNameValid_NameValid)
{
    std::string name1 = "Anna_M";
    ASSERT_TRUE(ServerAlgorythms::isNameValid(name1));
}