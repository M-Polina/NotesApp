//
// Created by Andrey Marusin on 23.12.2023.
//

#ifndef BOOSTBEAST_ECHOSERVER_ACCOUNT_H
#define BOOSTBEAST_ECHOSERVER_ACCOUNT_H

#include <vector>
#include <map>
#include <iostream>
#include <format>

#include "Note.h"

class Account {
public:
    Account();
    std::shared_ptr<std::vector<Note>> addAccount(std::string username);
    std::shared_ptr<std::vector<Note>> getAccountsNotes(std::string username);
    void addNoteToAccount(std::string username, Note new_note);
private:
    std::map<std::string, std::shared_ptr<std::vector<Note>>> accountsList;
};


#endif //BOOSTBEAST_ECHOSERVER_ACCOUNT_H
