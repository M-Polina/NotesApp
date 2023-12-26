#include <gtest/gtest.h>
#include "src/JsonParser.hpp"

TEST(JsonParserTest, CreateErrorJsonString)
{
    std::string str_err = "New error";
    std::string json_str = JsonParser::createErrorJsonString(str_err);
    ASSERT_EQ("{\"errorText\":\"New error\",\"type\":\"error\"}", json_str);
}

TEST(JsonParserTest, CreateLoginJsonString)
{
    std::string username = "Iron blade";
    std::string json_str = JsonParser::createLoginJsonString(username);

    ASSERT_EQ("{\"type\":\"login\",\"username\":\"Iron blade\"}", json_str);
}

TEST(JsonParserTest, СreateNotesJsonString)
{
    std::vector<Note> notes;
    Note n1("header 1", "text 1", "time 1");
    Note n2("header 2", "text 2", "time 2");

    notes.push_back(n1);
    notes.push_back(n2);

    std::string json_str = JsonParser::createNotesJsonString(notes);
    std::string notes_str = "{\"notes\":[{\"content\":\"text 1\",\"creationTime\":\"time 1\",\"header\":\"header 1\","
                  "\"type\":\"note\"},{\"content\":\"text 2\",\"creationTime\":\"time 2\",\"header\":\"header 2\","
                  "\"type\":\"note\"}],\"type\":\"notesList\"}";

    ASSERT_EQ(notes_str, json_str);
}

TEST(JsonParserTest, ParseErrorJson)
{
    std::string str_err = "Error appeared";
    std::string err_json_str = "{\"errorText\":\"Error appeared\",\"type\":\"error\"}";

    json error_json = JsonParser::stringToJson(err_json_str);
    std::string parse_result = JsonParser::parseErrorJson(error_json);

    ASSERT_EQ(str_err, parse_result);
}

TEST(JsonParserTest, ParseNotesJson)
{
    std::string str_err = "Error appeared";
    std::string err_json_str = "{\"errorText\":\"Error appeared\",\"type\":\"error\"}";

    json error_json = JsonParser::stringToJson(err_json_str);
    std::string parse_result = JsonParser::parseErrorJson(error_json);

    ASSERT_EQ(str_err, parse_result);
}

TEST(JsonParserTest, ParseLoginJson)
{
    std::string login_json_str = "{\"type\":\"login\",\"username\":\"Iron blade\"}";

    json login_json = JsonParser::stringToJson(login_json_str);
    std::string parse_result = JsonParser::parseLoginJson(login_json);

    ASSERT_EQ("Iron blade", parse_result);
}


TEST(JsonParserTest, ParseLoginJsonWithNoNotes)
{
//    std::string notes_json_str = "{\"notes\":[{\"content\":\"text 1\",\"creationTime\":\"time 1\",\"header\":\"header 1\","
//                                                         "\"type\":\"note\"},{\"content\":\"text 2\",\"creationTime\":\"time 2\",\"header\":\"header 2\","
//                                                         "\"type\":\"note\"}],\"type\":\"notesList\"}";;
    std::string notes_json_str = "{\"notes\":[],\"type\":\"notesList\"}";;

    json notes_json = JsonParser::stringToJson(notes_json_str);
    std::string parse_result = JsonParser::parseLoginJson(notes_json);

    ASSERT_EQ(0, parse_result.size());
}

TEST(JsonParserTest, ParseLoginJsonWithNotes)
{
    std::string notes_json_str = "{\"notes\":[{\"content\":\"text 1\",\"creationTime\":\"time 1\",\"header\":\"header 1\","
                                 "\"type\":\"note\"},{\"content\":\"text 2\",\"creationTime\":\"time 2\",\"header\":\"header 2\","
                                 "\"type\":\"note\"}],\"type\":\"notesList\"}";;

    json notes_json = JsonParser::stringToJson(notes_json_str);
    std::vector<Note> parse_result = JsonParser::parseNotesJson(notes_json);

    ASSERT_EQ(2, parse_result.size());

    ASSERT_EQ("time 1", parse_result[0].getCreationTime());
    ASSERT_EQ("header 1", parse_result[0].getHeader());
    ASSERT_EQ("text 1", parse_result[0].getContent());

    ASSERT_EQ("time 2", parse_result[1].getCreationTime());
    ASSERT_EQ("header 2", parse_result[1].getHeader());
    ASSERT_EQ("text 2", parse_result[1].getContent());
}