#include <gtest/gtest.h>
#include "src/Account.hpp"

TEST(AccountTest, AddAccaunt_DoesNotExist)
{
    std::string username1 = "Dina";
    std::string username2 = "Den";

    Account account;
    std::shared_ptr<std::vector<Note>>  account_notes;
    account_notes = account.addAccount(username1);

    ASSERT_EQ(0, account_notes->size());
    ASSERT_EQ(1, account.getAccountsListSize());

    account_notes = account.addAccount(username2);

    ASSERT_EQ(0, account_notes->size());
    ASSERT_EQ(2, account.getAccountsListSize());
}

TEST(AccountTest, AddAccaunt_AlreadyExist)
{
    std::string username1 = "Dina";

    Account account;
    std::shared_ptr<std::vector<Note>>  account_notes;
    account_notes = account.addAccount(username1);

    ASSERT_EQ(0, account_notes->size());
    ASSERT_EQ(1, account.getAccountsListSize());

    account_notes = account.addAccount(username1);

    ASSERT_EQ(0, account_notes->size());
    ASSERT_EQ(1, account.getAccountsListSize());
}

TEST(AccountTest, AddNote_NoSuchAccount)
{
    std::string username1 = "Dina";

    Account account;
    std::shared_ptr<std::vector<Note>>  account_notes;
    Note note("header 1", "text 1", "time 1");

    ASSERT_THROW(account.addNoteToAccount(username1, note), std::invalid_argument);
}

TEST(AccountTest, AddNote_AccountExists)
{
    std::string username1 = "Dina";

    Account account;
    account.addAccount(username1);

    Note note1("header 1", "text 1", "time 1");
    Note note2("header 2", "text 2", "time 2");

    account.addNoteToAccount(username1, note1);

    std::shared_ptr<std::vector<Note>>  account_notes;
    account_notes = account.getAccountsNotes(username1);
    ASSERT_EQ(1, account_notes->size());
    ASSERT_EQ("time 1", account_notes->at(0).getCreationTime());
    ASSERT_EQ("header 1", account_notes->at(0).getHeader());
    ASSERT_EQ("text 1", account_notes->at(0).getContent());

    account.addNoteToAccount(username1, note2);
    account_notes = account.getAccountsNotes(username1);
    ASSERT_EQ(2, account_notes->size());
    ASSERT_EQ("time 2", account_notes->at(1).getCreationTime());
    ASSERT_EQ("header 2", account_notes->at(1).getHeader());
    ASSERT_EQ("text 2", account_notes->at(1).getContent());
}

TEST(AccountTest, AddAccaunt_AlreadyExistWithNotes)
{
    std::string username1 = "Dina";

    Account account;
    std::shared_ptr<std::vector<Note>>  account_notes;
    account.addAccount(username1);

    Note note1("header 1", "text 1", "time 1");
    Note note2("header 2", "text 2", "time 2");

    account.addNoteToAccount(username1, note1);
    account.addNoteToAccount(username1, note2);

    account_notes = account.addAccount(username1);

    ASSERT_EQ(2, account_notes->size());
    ASSERT_EQ(1, account.getAccountsListSize());
}

