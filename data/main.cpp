#include <iostream>
#include <string_view>
#include <vector>
#include "Random.h"

namespace WordList
{
    std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size()-1)];
    }
}

class Session
{
private:
    
    std::string_view m_word { WordList::getRandomWord() };
    std::vector<bool> m_letterGuessed { std::vector<bool>(26) };

    std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }

public:
    std::string_view getWord() const { return m_word; }

    bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
    void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
};

void draw(const Session& s)
{
    std::cout << '\n';

    std::cout << "The word: ";
    for (auto c: s.getWord()) 
    {
        if (s.isLetterGuessed(c))
            std::cout << c;
        else
            std::cout << '_';
    }

    std::cout << '\n';
}

char getGuess(const Session& s)
{
    std::cout << "Enter your next letter: ";

    while (true)
    {
        char c{};
        std::cin >> c;

        if (!std::cin)
        {
            std::cin.clear();
            std::cout << "No not this word, try again\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c < 'a' || c > 'z')
        {
            std::cout << "No not this word, try again\n";
            continue;
        }

        if (s.isLetterGuessed(c))
        {
            std::cout << "You already guessed that work, try again.\n";
            continue;
        }

        return c;
    }
}

int main()
{
    std::cout << "Hello my friend, wellcome to my new project \n";
    std::cout << "Why don't we try to guess the word\n";

    Session s {};

    int count { 10 };
    while (--count)
    {
        draw(s);
        char c { getGuess(s) };
        s.setLetterGuessed(c);
    }

    draw(s);

    return 0;
}
