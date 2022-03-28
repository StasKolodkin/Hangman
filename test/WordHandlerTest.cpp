#include "WordHandler.h"
#include "catch.hpp"
#include <fstream>
#include <ostream>

TEST_CASE("No word base", "[wordhandler_class]")
{
    std::string errorMessage;
    try {
        WordHandler wordHandler;
        wordHandler.getRandomWord();
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "No word base!");
}

TEST_CASE("Available word base", "[wordhandler_class]")
{
    std::string errorMessage;
    try {
        WordHandler wordHandler;
        wordHandler.addWord("today");
        wordHandler.getRandomWord();
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage.empty());
}

TEST_CASE(
        "Added word contains characters that are not letters",
        "[wordhandler_class]")
{
    std::string errorMessage;
    try {
        WordHandler wordHandler;
        wordHandler.addWord("2day");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage
            == "The word contains characters that are not letters <2day>!");
}

TEST_CASE("Added valid word", "[wordhandler_class]")
{
    std::string errorMessage;
    try {
        WordHandler wordHandler;
        wordHandler.addWord("today");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage.empty());
}

TEST_CASE("Unable to open file", "[wordhandler_class]")
{
    std::string errorMessage;
    try {
        WordHandler wordHandler;
        wordHandler.importFromFIle("non-existent file");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "Unable to open file <non-existent file> !");
}

TEST_CASE("File can be open", "[wordhandler_class]")
{
    std::ofstream out("test_file.txt");
    out << "good" << std::endl;
    out.close();
    std::string errorMessage;
    try {
        WordHandler wordHandler;
        wordHandler.importFromFIle("test_file.txt");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    std::remove("test_file.txt");
    REQUIRE(errorMessage == "");
}