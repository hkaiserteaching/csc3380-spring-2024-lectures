
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using category = std::string;
using rule = std::vector<std::string>;
using rule_collection = std::vector<rule>;
using grammar = std::map<category, rule_collection>;

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

// read a grammar from a given input stream
grammar read_grammar(std::istream& in)
{
    grammar ret;
    std::string line;
    // read the input
    while (std::getline(in, line))
    {
        // split the input into words
        std::vector<std::string> entry = split(line);
        if (!entry.empty())
        {
            // use the category to store the associated rule
            ret[entry[0]].push_back(rule(entry.begin() + 1, entry.end()));
        }
    }
    return ret;
}

// return a random integer in the range [0, n)
int nrand(int n)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, n - 1);
    return dist(mt);
}

// return true if 's' represents a category
bool bracketed(std::string const& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void generate_aux(
    grammar const& g, std::string const& word, std::vector<std::string>& ret)
{
    if (!bracketed(word))
    {
        ret.push_back(word);
    }
    else
    {
        // locate the rule that corresponds to word
        auto it = g.find(word);
        if (it == g.end())
            throw std::logic_error("empty rule");

        // fetch the set of possible rules
        rule_collection const& c = it->second;

        // from which we select one at random
        rule const& r = c[nrand(c.size())];

        // recursively expand the selected rule
        for (auto i = r.begin(); i != r.end(); ++i)
            generate_aux(g, *i, ret);
    }
}

std::vector<std::string> generate_sentence(grammar const& g)
{
    std::vector<std::string> ret;
    generate_aux(g, "<sentence>", ret);
    return ret;
}

char const* grammar_str = R"(
    <noun> 	        cat
    <noun> 	        dog
    <noun> 	        table
    <noun-phrase> 	<noun>
    <noun-phrase> 	<adjective> <noun-phrase>
    <adjective> 	large
    <adjective> 	brown
    <adjective> 	absurd
    <verb> 	        jumps
    <verb> 	        sits
    <location> 	    on the stairs
    <location>	    under the sky
    <location> 	    wherever it wants
    <sentence> 	    the <noun-phrase> <verb> <location>
)";

int main()
{
    std::stringstream input(grammar_str);

    grammar g = read_grammar(input);

    for (int i = 0; i != 10; ++i)
    {
        // generate the sentence
        std::vector<std::string> sentence = generate_sentence(g);

        // write the first word, if any
        auto it = sentence.begin();
        if (!sentence.empty())
            std::cout << *it++;

        // write the rest of the words, each preceded by a space
        std::for_each(it, sentence.end(),
            [](std::string const& s) { std::cout << " " << s; });

        std::cout << std::endl;
    }
    return 0;
}
