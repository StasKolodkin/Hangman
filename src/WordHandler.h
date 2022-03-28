#ifndef WORDHANLER_H
#define WORDHANLER_H

#include <random>
#include <stdexcept>
#include <string>
#include <vector>

class WordHandler {
private:
    std::vector<std::string> words;

    bool wordIsValid(const std::string& word)
    {
        if (word.empty())
            return false;
        for (auto i = 0; i < word.length(); ++i)
            if (toupper(word[i]) < 'A' || toupper(word[i]) > 'Z')
                return false;
        return true;
    }

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
    void addWord(const std::string& word)
    {
        if (wordIsValid(word))
            words.push_back(word);
        else
            throw std::runtime_error(
                    "The word contains characters that are not letters <" + word
                    + ">!");
    }
};

#endif