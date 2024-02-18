#include <functional>
#include <iostream>

#include "power.hpp"
#include "matrix.hpp"

int fib(int n)
{
    if (n < 2)
        return n;

    auto result = power_semigroup(
        matrix{1, 1, 1, 0}, n - 1, std::multiplies<matrix<int>>());

    return result.x11;
}

int main()
{
    int num;
    std::cout << "Enter the number : ";
    std::cin >> num;
    std::cout << "\nThe fibonacci number : " << fib(num) << '\n';
    return 0;
}
