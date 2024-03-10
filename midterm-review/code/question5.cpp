#include <iostream>

int main()
{
    int const max = 5;
    int i = 0;
    while (i < max) {
        std::cout << i << " + 3 == " << i + 3 << std::endl;
        ++i;
    }
    return 0;
}
