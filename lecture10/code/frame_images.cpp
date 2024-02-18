
#include <iostream>
#include <string>
#include <vector>

#include "ascii_image.hpp"
#include "framed_image.hpp"

int main()
{
    std::vector<std::string> example = {
        "this is an", "example", "to illustrate", "framing"};

    image img(example);

    std::cout << frame(img, 3);
    std::cout << framed_image(img, 3);

    return 0;
}