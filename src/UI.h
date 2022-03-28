#ifndef UI_H
#define UI_H

#include "Hangman.h"
#include "WordHandler.h"
#include "entity/Colors.h"
#include <csignal>
#include <iostream>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

class UI {
private:
    Hangman hangman;
    WordHandler wordHandler;
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
        setForegroundColor(Colors::Reset);
    }
    void drawWelcomeScreen()
    {
        cleanScreen();
        drawLogo();
        drawRules();
        std::cout << "Press any key to continue..." << std::endl;
        getChar();
    }
    void drawGameOverBanner(short lives)
    {
        if (lives == 0) {
            setForegroundColor(Colors::Red);
            std::cout << "__   _____  _   _   ____ ___ _____ ____\n"
                         "\\ \\ / / _ \\| | | | |  _ \\_ _| ____|  _ \\\n"
                         " \\ V / | | | | | | | | | | ||  _| | | | |\n"
                         "  | || |_| | |_| | | |_| | || |___| |_| |\n"
                         "  |_| \\___/ \\___/  |____/___|_____|____/";
            std::cout << std::endl;
        } else {
            setForegroundColor(Colors::Green);
            std::cout << "__   _____  _   _  __        _____ _   _\n"
                         "\\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | |\n"
                         " \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| |\n"
                         "  | || |_| | |_| |   \\ V  V /  | || |\\  |\n"
                         "  |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_|";
            std::cout << std::endl;
        }
        setForegroundColor(Colors::Reset);
        std::cout << std::endl;
    }
    void drawHangmanPicture(short lives)
    {
        setForegroundColor(Colors::White);
        short headPos = 46;
        short bodyPos = 59;
        short leftHandPos = 44;
        short rightHandPos = 48;
        short leftLegPos = 71;
        short rightLegPos = 73;
        std::string picture
                = "            \n"
                  "  ______    \n"
                  "  |    |    \n"
                  "  |         \n"
                  "  |         \n"
                  "  |         \n"
                  "  |         \n"
                  "__|_____    \n"
                  "|       |___\n"
                  "|__________|\n";
        if (lives < 6)
            picture[headPos] = 'O';
        if (lives < 5)
            picture[bodyPos] = '|';
        if (lives < 4)
            picture[leftHandPos] = '\\';
        if (lives < 3)
            picture[rightHandPos] = '/';
        if (lives < 2)
            picture[leftLegPos] = '/';
        if (lives < 1)
            picture[rightLegPos] = '\\';
        std::cout << picture << std::endl;
        setForegroundColor(Colors::Reset);
    }
    void drawHiddenWord(const std::string& hiddenWord)
    {
        setForegroundColor(Colors::Green);
        std::cout << "   Word:  " << hiddenWord << std::endl << std::endl;
        setForegroundColor(Colors::Reset);
    }
    void drawGuessedLetters(const std::string& guessedLetters)
    {
        setForegroundColor(Colors::Magenta);
        std::cout << "Guessed:  ";
        for (u_long i = 0; i < guessedLetters.length(); ++i) {
            if (i != 0)
                std::cout << ", ";
            std::cout << guessedLetters[i];
        }
        std::cout << std::endl << std::endl;
        setForegroundColor(Colors::Reset);
    }
    void draw(const HangmanState& currentState)
    {
        cleanScreen();
        drawHangmanPicture(currentState.lives);
        drawHiddenWord(currentState.hiddenWord);
        drawGuessedLetters(currentState.guessedLetters);
    }

public:
    void show()
    {
        setBackgroundColor(Colors::Black);
        std::setbuf(stdout, nullptr);
        drawWelcomeScreen();

        auto currentState = hangman.start(wordHandler.getRandomWord());
        char letter;

        draw(currentState);
        while (!hangman.isGameOver()) {
            if ((letter = getChar()) != '\0')
                currentState = hangman.checkLetter(letter);
            draw(currentState);
        }

        drawGameOverBanner(currentState.lives);
        setBackgroundColor(Colors::Reset);
    }
};

#endif
