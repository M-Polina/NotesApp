//
// Created by Andrey Marusin on 23.12.2023.
//

#include "Account.h"
Account::Account() {
     std::map<std::string, std::shared_ptr<std::vector<Note>>> accountsList;
}

std::shared_ptr<std::vector<Note>> Account::addAccount(std::string username) {
    std::map<std::string, std::shared_ptr<std::vector<Note>>>::iterator it;
    it = accountsList.find(username);

    if (it != accountsList.end())
        return accountsList[username];

    auto shared_notes = std::make_shared<std::vector<Note>>();
    accountsList[username] = shared_notes;

    return shared_notes;
}

std::shared_ptr<std::vector<Note>> Account::getAccountsNotes(std::string username) {
    std::map<std::string, std::shared_ptr<std::vector<Note>>>::iterator it;
    it = accountsList.find(username);

    if (it != accountsList.end())
        return accountsList[username];

    auto shared_notes = std::make_shared<std::vector<Note>>();
    return shared_notes;
}

//void addNoteToAccount(std::string Account::username, Note new_note) {}