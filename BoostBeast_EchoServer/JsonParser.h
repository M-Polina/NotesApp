//
// Created by Andrey Marusin on 23.12.2023.
//

#ifndef BOOSTBEAST_ECHOSERVER_JSONPARSER_H
#define BOOSTBEAST_ECHOSERVER_JSONPARSER_H

#include <istream>
#include "nlohmann/json.hpp"
#include "Note.h"

using json = nlohmann::json;
static const std::string LOGIN_TYPE = "login";
static const std::string NOTES_TYPE = "notesList";

static class JsonParser {
    JsonParser();
public:
    static std::string createLoginJsonString(std::string username);
    static std::string createNotesJsonString(std::vector<Note> &notes);
    static json stringToJson(std::string json_string);
    static std::vector<Note> &parseNotesJson(json notes_json);
    static std::string parseLoginJson(json json);
};


#endif //BOOSTBEAST_ECHOSERVER_JSONPARSER_H
