#ifndef UI_H
#define UI_H

#include "Hangman.h"

class UI {
private:
    Hangman hangman;

public:
    void show()
    {
        std::setbuf(stdout, nullptr);
    }
};

#endif
