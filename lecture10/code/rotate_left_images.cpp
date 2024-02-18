
#include <iostream>
#include <string>
#include <vector>

#include "ascii_image.hpp"

int main()
{
    std::vector<std::string> example = {
        "this is an", "example", "to", "illustrate", "rotation"};

    image img(example);
    std::cout << hcat(img, rotate_left(img));

    return 0;
}