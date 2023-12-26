#include <gtest/gtest.h>
#include "src/Note.hpp"

TEST(NoteTest, CreateNote)
{
    std::string header = "header";
    std::string text = "text";
    std::string date = "date";
    Note note(header, text, date);

    ASSERT_EQ(date, note.getCreationTime());
    ASSERT_EQ(header, note.getHeader());
    ASSERT_EQ(text, note.getContent());
}