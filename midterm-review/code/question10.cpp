#include <iostream>
#include <stdexcept>

double sqrt(double x);   // declaration only

double square_root(double x)
{
    // what goes here?
    if (x < 0)
        throw std::runtime_error("duh!");
    return sqrt(x);
}

int main()
{
    try {
        square_root(-1);
    }
    catch(std::runtime_error e)
    {
        std::cout << e.what() << "\n";
    }
    return 0;
}