#ifndef UI_H
#define UI_H

#include "Hangman.h"
#include "entity/Colors.h"
#include <iostream>

class UI {
private:
    Hangman hangman;
    void cleanScreen()
    {
        std::cout << "\033c";
    }
    void setForegroundColor(Colors color)
    {
        std::cout << "\E[3" << color << "m";
    }
    void setBackgroundColor(Colors color)
    {
        std::cout << "\E[4" << color << "m";
    }

public:
    void show()
    {
        std::setbuf(stdout, nullptr);
        cleanScreen();
    }
};

#endif
