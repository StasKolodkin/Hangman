#ifndef WORDHANLER_H
#define WORDHANLER_H

#include <random>
#include <stdexcept>
#include <string>
#include <vector>

class WordHandler {
private:
    std::vector<std::string> words;

public:
    std::string getRandomWord()
    {
        if (words.empty())
            throw std::runtime_error("No word base!");
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<u_long> distribution(0, words.size());
        return words[distribution(generator)];
    }
};

#endif