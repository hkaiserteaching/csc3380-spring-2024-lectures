// WRITE A PROGRAM THAT PROMPTS THE USER TO ENTER SOME WORDS AND
// WHICH READS THOSE WORDS INTO A vector<string>. PRINT THE WORDS 
// IN LEXICOGRAPHICAL ORDER SEPARATELY EACH ONE ON A SEPARATE LINE 
// TO THE CONSOLE AFTER ALL WORDS HAVE BEEN READ. PRINT THE LENGTH 
// (IN TERMS OF NUMBER OF CHARACTERS) OF THE SHORTEST AND THE 
// LONGEST WORD, AND THE AVERAGE LENGTH OF ALL WORDS IN THE END. 

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::cout << "Please enter some words: ";
    std::vector<std::string> words;

    std::string word;
    while (std::cin >> word)
        words.push_back(word);

    std::sort(words.begin(), words.end());

    for (std::string const& s: words)
        std::cout << s << "\n";

    std::string::size_type minlen = 1000;
    for (std::string const& s: words)
    {
        if (minlen > s.size())
            minlen = s.size();
    }

    std::string::size_type maxlen = 0;
    for (std::string const& s: words)
        maxlen = std::max(maxlen, s.size());

    std::cout << "Minimal length: " << minlen << "\n";
    std::cout << "Maximal length: " << maxlen << "\n";

    std::string::size_type avglen = 0;
    for (std::string const& s: words)
        avglen += s.size();

    std::cout << "Average length: " << avglen / words.size() << "\n";

    return 0;
}
