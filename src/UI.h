#ifndef UI_H
#define UI_H

#include "Hangman.h"
#include <iostream>

class UI {
private:
    Hangman hangman;
    void cleanScreen()
    {
        std::cout << "\033c";
    }

public:
    void show()
    {
        std::setbuf(stdout, nullptr);
        cleanScreen();
    }
};

#endif
