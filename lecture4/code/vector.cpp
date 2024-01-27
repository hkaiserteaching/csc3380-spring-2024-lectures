#include <cstdint>
#include <iostream>
#include <vector>

void initialize_vector()
{
    // An array of integers, initialized with five elements:
    std::vector<std::int64_t> data{1, 2, 3, 4, 5};

    // Elements can be accessed using the operator []
    std::cout << "data[3] == " << data[3] << "\n";    // data[3] == 4

    // An array of arrays of integers follows the same pattern
    std::vector<std::vector<std::int64_t>> data2d{
        {1, 2, 3}, {2, 3}, {4, 5, 6}, {7}};

    // Same logic for accessing elements
    std::cout << "data2d[1][0] == " << data2d[1][0]
              << "\n";    // data2d[1][0] == 2
    std::cout << "data2d[2][2] == " << data2d[2][2]
              << "\n";    // data2d[2][2] == 6

    // We can use element access to mutate the array
    data2d[3] = {1, 2, 3, 4, 5};
    std::cout << "data2d[3][2] == " << data2d[3][2]
              << "\n";    // data2d[3][2] == 3
    data2d[1][0] = 42;
    std::cout << "data2d[1][0] == " << data2d[1][0]
              << "\n";    // data2d[1][0] == 42
}

int main()
{
    initialize_vector();

    return 0;
}