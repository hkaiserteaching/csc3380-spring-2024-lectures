
#include <iostream>

int sum(int x)
{
    std::cout << x << std::endl;
    if (x == 4)
        return 4;
    return sum(x + 1) + x;
}

int main()
{
    std::cout << sum(1) << std::endl;
    return 0;
}
