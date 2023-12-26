#pragma once
#ifndef BOOSTBEAST_ECHOSERVER_NOTE_H
#define BOOSTBEAST_ECHOSERVER_NOTE_H

#include <string>

class Note {
public:
    Note(std::string header, std::string noteText, std::string creationTime);

private:
    std::string header_;
    std::string noteText_;
    std::string creationTime_;
public:
    std::string getHeader();
    std::string getContent();
    std::string getCreationTime();
};


#endif //BOOSTBEAST_ECHOSERVER_NOTE_H
