
#include <stdexcept>
#include <iostream>

int main()
{
    std::cout << "Testing exceptions." << std::endl;
    try {
        throw std::runtime_error("Doh! Something went wrong!");
        std::cout << "Here we are, still alive and kicking!" << std::endl;
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Done testing exceptions." << std::endl;
    return 0;
}
