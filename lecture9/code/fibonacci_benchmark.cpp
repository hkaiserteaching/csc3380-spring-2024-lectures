
#include <utility>

#include "power.hpp"
#include "matrix.hpp"
#include "catch.hpp"

int fib_sequential(int n)
{
    if (n == 0)
        return 0;
        
    std::pair<int, int> v = {0, 1};
    for (int i = 0; i < n - 1; i++)
    {
        v = {v.second, v.first + v.second};
    }
    return v.first;
}

PROVIDED_TEST("sequential fibonacci")
{
    for (int i = 1; i <= 32 * 1024 * 1024; i = 2 * i)
    {
        BENCHMARK("execution time for fib: " + std::to_string(i))
        {
            return fib_sequential(i);
        };
    }
}

int fib(int n)
{
    if (n < 2)
        return n;

    auto result = power_semigroup(
        matrix{1, 1, 1, 0}, n - 1, std::multiplies<matrix<int>>());

    return result.x11;
}

PROVIDED_TEST("power fibonacci")
{
    for (int i = 1; i <= 32 * 1024 * 1024; i = 2 * i)
    {
        BENCHMARK("execution time for fib: " + std::to_string(i))
        {
            return fib(i);
        };
    }
}
