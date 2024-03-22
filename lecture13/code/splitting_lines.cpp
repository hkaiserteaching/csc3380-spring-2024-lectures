#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string const& s)
{
    std::vector<std::string> words;
    std::vector<std::string>::size_type i = 0;

    // invariant: we have processed characters [original value of i, i)
    while (i != s.size())
    {
        // invariant: characters in range [original i, current i)
        // are all spaces
        while (i != s.size() && std::isspace(s[i]))    // short-circuiting
            ++i;

        // find end of next word
        auto j = i;

        // invariant: none of the characters in range
        // [original j, current j) is a space
        while (j != s.size() && !std::isspace(s[j]))    // short-circuiting
            ++j;

        // if we found some non-whitespace characters, store the word
        if (i != j)
        {
            // copy from s starting at i and having j – i characters
            words.push_back(s.substr(i, j - i));
            i = j;
        }
    }

    return words;
}

int main()
{
    std::string line;
    if (std::getline(std::cin, line))
    {
        std::vector<std::string> words = split(line);
        for (auto const& word : words)
            std::cout << word << '\n';
    }

    return 0;
}
