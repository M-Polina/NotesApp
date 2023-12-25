#include "JsonParser.h"
#include <iostream>


JsonParser::JsonParser() { }

std::string JsonParser::createLoginJsonString(std::string username) {
    json loginJson;
    loginJson["type"] = LOGIN_TYPE;
    loginJson["username"] = username;

    return loginJson.dump();
}

std::string JsonParser::createNotesJsonString(std::vector<Note> &notes) {
    json notesJson;
    notesJson["type"] = NOTES_TYPE;

    auto jsonNotes = json::array();
    for(auto i = 0; i < notes.size(); ++i) {
        json note;
        note["type"] = "note";
        note["header"] = notes[i].getHeader();
        note["content"] = notes[i].getContent();
        note["creationTime"] = notes[i].getCreationTime();

        jsonNotes.push_back(note);
    }

    notesJson["notes"] = jsonNotes;

    return  notesJson.dump();
}

json JsonParser::stringToJson(std::string json_string) {
    json parsed_json = json::parse(json_string);

    return parsed_json;
}

std::vector<Note> &JsonParser::parseNotesJson(json notes_json) {
    std::vector<Note> *notesList = new std::vector<Note>();
    if (notes_json.find("type") == notes_json.end()) {
        return *notesList;
    }
    std::string type = notes_json.at("type");

    if (type != NOTES_TYPE) {
        std::cout  << "parsing Login Json: Not notesList type!";
        return *notesList;
    }


    for (auto &json_note : notes_json.at("notes")) {
        Note note(json_note.at("header"), json_note.at("content"),  json_note.at("creationTime"));
        notesList->push_back(note);
    }

    return *notesList;
}

std::string JsonParser::parseLoginJson(json json) {
    if (json.find("type") == json.end()) {
        return "";
    }
    std::string type = json.at("type");

    if (type != LOGIN_TYPE) {
        std::cout  << "parsing Login Json: Not login type!";
        return "";
    }

    std::string username = json.at("username");

    return username;
}

std::string JsonParser::parseErrorJson(json error_json) {
    if (error_json.find("type") == error_json.end()) {
        return "";
    }
    std::string type = error_json.at("type");

    if (type != ERROR_TYPE) {
        std::cout << "parsing Error Json: Not error type!";
        return "";
    }

    std::string error = error_json.at("errorText");

    return error;
}

std::string JsonParser::createErrorJsonString(std::string error) {
    json errorJson;
    errorJson["type"] = ERROR_TYPE;

    errorJson["errorText"] = error;

    return errorJson.dump();
}
