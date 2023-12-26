#pragma once
#ifndef BOOSTBEAST_ECHOSERVER_JSONPARSER_H
#define BOOSTBEAST_ECHOSERVER_JSONPARSER_H

#include <iostream>
#include "nlohmann/json.hpp"
#include "Note.hpp"

using json = nlohmann::json;
static const std::string LOGIN_TYPE = "login";
static const std::string NOTES_TYPE = "notesList";
static const std::string ERROR_TYPE="error";

class JsonParser {
    JsonParser();
public:
    static std::string createLoginJsonString(std::string username);
    static std::string createNotesJsonString(std::vector<Note> &notes);
    static std::string createErrorJsonString(std::string error);
    static json stringToJson(std::string json_string);
    static std::vector<Note> &parseNotesJson(json notes_json);
    static std::string parseLoginJson(json json);
    static std::string parseErrorJson(json error_json);
};


#endif //BOOSTBEAST_ECHOSERVER_JSONPARSER_H
