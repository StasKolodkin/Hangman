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

    void drawLogo()
    {
        setForegroundColor(Colors::Cyan);
        std::cout << " _\n"
                     "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n"
                     "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n"
                     "| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
                     "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
                     "                   |___/";
        std::cout << std::endl;
        setForegroundColor(Colors::Reset);
    }

public:
    void show()
    {
        std::setbuf(stdout, nullptr);
        cleanScreen();
        drawLogo();
    }
};

#endif
