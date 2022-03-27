#include "Hangman.h"
#include "catch.hpp"

TEST_CASE("Correctness of initialization", "[hangman_class]")
{
    std::string errorMessage;
    Hangman hangman;
    HangmanState startState = hangman.start("initialization");
    REQUIRE(startState.lives == 6);
    REQUIRE(startState.guessedLetters.empty());
    REQUIRE(startState.hiddenWord == "______________");
}

TEST_CASE("Word is empty", "[hangman_class]")
{
    std::string errorMessage;
    Hangman hangman;
    try {
        HangmanState startState = hangman.start("");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "Word is empty!");
}

TEST_CASE(
        "The word contains characters that are not letters", "[hangman_class]")
{
    std::string errorMessage;
    Hangman hangman;
    try {
        HangmanState startState = hangman.start("2day");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage
            == "The word contains characters that are not letters!");
}
