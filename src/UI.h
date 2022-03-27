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
    void drawRules()
    {
        setBackgroundColor(Colors::Black);
        setForegroundColor(Colors::Green);
        std::cout << std::endl << "RULES:" << std::endl;
        std::cout
                << "The word is guessed.\n\n"
                   "You suggest a letter that can be part of this word. If "
                   "there "
                   "is such a letter in the word, then it is written over the "
                   "lines corresponding to this letter - as many times as it "
                   "occurs in the word. If there is no such letter, then a "
                   "circle in a loop representing the head is added to the "
                   "gallows. For each subsequent incorrect answer, one part of "
                   "the torso is added to the gallows.\n\n"
                   "If the torso in the gallows is drawn completely, then the "
                   "guessing player loses, it is considered hanged. If the "
                   "player manages to guess the word, he wins.\n"
                << std::endl;
        setBackgroundColor(Colors::Reset);
        setForegroundColor(Colors::Reset);
    }

public:
    void show()
    {
        std::setbuf(stdout, nullptr);
        cleanScreen();
    }
};

#endif
