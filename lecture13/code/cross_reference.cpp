#include <algorithm>
#include <iostream>
#include <map>
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

std::map<std::string, std::vector<int>> xref(std::istream& in,
    std::vector<std::string> find_words(std::string const&) = split)
{
    std::string line;                               // current line
    int line_number = 0;                            // current line number
    std::map<std::string, std::vector<int>> ret;    // cross reference table

    // read the next line
    while (std::getline(in, line))
    {
        // adjust current line number
        ++line_number;

        // break the input line into words
        std::vector<std::string> words = find_words(line);

        // remember that each word occurs on the current line
        for (auto const& s : words)
        {
            ret[s].push_back(line_number);
        }
    }

    return ret;
}


int main()
{
    // call xref using split by default
    std::map<std::string, std::vector<int>> xref_map = xref(std::cin);

    // write the results
    for (auto it = xref_map.begin(); it != xref_map.end(); ++it)
    {
        // write the word followed by one or more line numbers
        std::cout << it->first << " occurs on line(s): ";

        auto line_it = it->second.begin();
        std::cout << *line_it++;    // write the first line number

        // write the rest of the line numbers, if any
        std::for_each(line_it, it->second.end(),
            [](int line) { std::cout << ", " << line; });

        // write a new line to separate each word from the next
        std::cout << std::endl;
    }
    return 0;
}
