#ifndef UI_H
#define UI_H

#include "Hangman.h"
#include "entity/Colors.h"
#include <csignal>
#include <iostream>
#include <termios.h>

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
    char getChar()
    {
        termios userTerminalSettings{};
        int vtime = 0, vmin = 1;

        if (tcgetattr(0, &userTerminalSettings) != 0)
            throw std::runtime_error("Unable to get terminal settings!");

        termios customTerminalSettings = userTerminalSettings;

        customTerminalSettings.c_lflag &= ~ICANON;
        customTerminalSettings.c_cc[VTIME] = vtime;
        customTerminalSettings.c_cc[VMIN] = vmin;
        customTerminalSettings.c_lflag &= ~ECHO;
        customTerminalSettings.c_lflag |= ISIG;

        if (tcsetattr(0, TCSANOW, &customTerminalSettings) != 0)
            throw std::runtime_error("Unable to set custom terminal settings!");

        char buf[8]{};
        read(STDIN_FILENO, buf, 8);

        if (tcsetattr(0, TCSANOW, &userTerminalSettings) != 0)
            throw std::runtime_error(
                    "Unable to restore user terminal settings!");

        if (toupper(buf[0]) >= 'A' && toupper(buf[0]) <= 'Z')
            return buf[0];
        else
            return '\0';
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
