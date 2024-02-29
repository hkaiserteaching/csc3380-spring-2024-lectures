
#include <cstdint>
#include <iostream>

#include "list.hpp"

void print(list<char> const& l)
{
    // Print contents of list.
    for (char c : l)
    {
        std::cout << c << " ";
    }

    std::cout << std::endl;
}

int main()
{
    list<char> l;

    // Create a list "a b c",
    l.push_back('a');
    l.push_back('b');
    l.push_back('c');

    print(l);

    // delete first element
    l.erase(l.begin());

    print(l);

    return 0;
}