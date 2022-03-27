#ifndef HANGMAN_H
#define HANGMAN_H

#include "entity/HangmanState.h"
#include <algorithm>
#include <stdexcept>
#include <string>

class Hangman {
private:
    std::string word;
    HangmanState state;

    void validateWord(const std::string& wd)
    {
        if (wd.empty())
            throw std::runtime_error("Word is empty!");
        for (u_long i = 0; i < wd.length(); ++i)
            if (toupper(wd[i]) < 'A' || toupper(wd[i]) > 'Z')
                throw std::runtime_error(
                        "The word contains characters that are not letters!");
    }

public:
    HangmanState start(const std::string& wd)
    {
        validateWord(wd);
        word = wd;
        state.lives = 6;
        state.guessedLetters.clear();
        state.hiddenWord = std::string(word.length(), '_');
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        return state;
    }
};

#endif