
#include <iostream>
#include <string>
#include <vector>

#include "ascii_image.hpp"

int main()
{
    std::vector<std::string> example = {
        "this is an", "example", "to", "illustrate", "framing"};

    image img(example);
    image framed = frame(img, 3);
    std::cout << hcat(img, framed);

    return 0;
}