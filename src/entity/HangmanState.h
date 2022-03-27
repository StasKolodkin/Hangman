#ifndef HANGMANSTATE_H
#define HANGMANSTATE_H

#include <string>

struct HangmanState {
    short lives{};
    std::string hiddenWord{};
    std::string guessedLetters{};
};

#endif
