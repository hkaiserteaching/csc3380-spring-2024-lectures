
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::string s;
    std::map<std::string, int> counters;    // store each word and an
                                            // associated counter
                                            
    // read the input, keeping track of each word and
    // how often we see it
    while (std::cin >> s)
        ++counters[s];

    // write the words and associated counts
    for (std::map<std::string, int>::const_iterator it = counters.begin();
         it != counters.end(); ++it)
    {
        std::cout << it->first << "\t" << it->second << std::endl;
    }

    return 0;
}
