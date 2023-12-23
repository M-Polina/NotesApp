//
// Created by Andrey Marusin on 23.12.2023.
//

#include "Note.h"

Note::Note(std::string header, std::string noteText, std::string creationTime) {
    header_ = header;
    noteText_ = noteText;
    creationTime_ = creationTime;
}

std::string Note::getHeader() {
    return header_;
}

std::string Note::getContent() {
    return noteText_;
}

std::string Note::getCreationTime() {
    return creationTime_;
}
