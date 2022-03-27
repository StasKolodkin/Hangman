#ifndef HANGMAN_H
#define HANGMAN_H

#include "entity/HangmanState.h"

class Hangman {
private:
    std::string word;
    HangmanState state;
};

#endif