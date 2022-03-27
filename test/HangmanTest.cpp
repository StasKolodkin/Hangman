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

TEST_CASE("Using checkLetter but game is not started", "[hangman_class]")
{
    std::string errorMessage;
    try {
        Hangman hangman;
        hangman.checkLetter('%');
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "Game is not started!");
}

TEST_CASE("Received symbol is not a letter", "[hangman_class]")
{
    std::string errorMessage;
    try {
        Hangman hangman;
        hangman.start("Good");
        hangman.checkLetter('%');
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "The received symbol is not a letter!");
}

TEST_CASE("Win", "[hangman_class]")
{
    Hangman hangman;
    HangmanState startState = hangman.start("Win");
    hangman.checkLetter('w');
    hangman.checkLetter('I');
    HangmanState finalState = hangman.checkLetter('N');
    REQUIRE(hangman.isGameOver());
    REQUIRE(startState.lives == finalState.lives);
    REQUIRE(finalState.guessedLetters == "WIN");
    REQUIRE(finalState.hiddenWord == "WIN");
}

TEST_CASE("Lose", "[hangman_class]")
{
    Hangman hangman;
    HangmanState startState = hangman.start("loSE");
    hangman.checkLetter('z');
    hangman.checkLetter('x');
    hangman.checkLetter('c');
    hangman.checkLetter('v');
    hangman.checkLetter('b');
    HangmanState finalState = hangman.checkLetter('n');
    REQUIRE(hangman.isGameOver());
    REQUIRE(finalState.lives == 0);
    REQUIRE(startState.hiddenWord == finalState.hiddenWord);
    REQUIRE(finalState.guessedLetters == "ZXCVBN");
}
