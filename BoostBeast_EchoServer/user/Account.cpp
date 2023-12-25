#include "Account.h"

Account::Account() {
    std::map<std::string, std::shared_ptr<std::vector<Note>>> accountsList;
}

std::shared_ptr<std::vector<Note>> Account::addAccount(std::string username) {
    std::cout << accountsList.size() << std::endl;
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

void Account::addNoteToAccount(std::string username, Note new_note) {
    std::map<std::string, std::shared_ptr<std::vector<Note>>>::iterator it;
    it = accountsList.find(username);

    if (it == accountsList.end())
        throw std::invalid_argument("No account with username " + username + "!");

    accountsList[username]->push_back(new_note);

    std::cout << "accountsList len: " << accountsList[username]->size() << std::endl;
}