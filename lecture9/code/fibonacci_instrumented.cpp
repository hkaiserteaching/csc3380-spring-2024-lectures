
#include <iostream>
#include <utility>

#include "count_operations.hpp"
#include "instrumented.hpp"
#include "matrix.hpp"
#include "power.hpp"

long fib_sequential(int n)
{
    if (n == 0)
        return 0;

    std::pair<instrumented<long>, instrumented<long>> v = {0, 1};
    for (int i = 0; i < n - 1; i++)
    {
        v = {v.second, v.first + v.second};
    }
    return v.first.value;
}

long fib(int n)
{
    if (n < 2)
        return n;

    auto result = power_semigroup(matrix<instrumented<long>>{1, 1, 1, 0}, n - 1,
        std::multiplies<matrix<instrumented<long>>>());

    return result.x11.value;
}

long fib_instrumented_matrix(int n)
{
    if (n < 2)
        return n;

    auto result = power_semigroup(instrumented<matrix<long>>{matrix{1l, 1l, 1l, 0l}},
        n - 1, std::multiplies<instrumented<matrix<long>>>());

    return result.value.x11;
}

struct fib_sequential_functor
{
    long operator()(int i) const
    {
        return fib_sequential(i);
    }
};

struct fib_functor
{
    long operator()(int i) const
    {
        return fib(i);
    }
};

struct fib_instrumented_matrix_functor
{
    long operator()(int i) const
    {
        return fib_instrumented_matrix(i);
    }
};

int main(int argc, char* argv[])
{
    // count operations
    std::cout << "fib_sequential" << std::endl;
    count_operations<instrumented<int>>(
        16, 32 * 1024 * 1024, fib_sequential_functor());

    std::cout << "fib" << std::endl;
    count_operations<instrumented<int>>(
        16, 32 * 1024 * 1024, fib_functor());

    std::cout << "fib_instrumented_matrix" << std::endl;
    count_operations<instrumented<matrix<int>>>(
        16, 32 * 1024 * 1024, fib_instrumented_matrix_functor());

    return 0;
}
