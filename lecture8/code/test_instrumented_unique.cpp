#include <algorithm>
#include <concepts>
#include <set>

#include "catch.hpp"
#include "count_operations.hpp"

struct set_functor
{
    template <typename I>
        requires(std::random_access_iterator<I>)
    int operator()(I first, I last) const
    {
        std::set<std::iter_value_t<I>> a(first, last);
        return a.size();
    }
};

struct unique_functor
{
    template <typename I>
        requires(std::random_access_iterator<I>)
    int operator()(I first, I last) const
    {
        std::sort(first, last);
        return std::unique(first, last) - first;
    }
};

PROVIDED_TEST("unique and sort")
{
    for (int i = 16; i <= 8 * 1024 * 1024; i = 2 * i)
    {
        BENCHMARK("execution time for array size " + std::to_string(i))
        {
            return count_operations(
                i, i, unique_functor(), dont_normalize, false);
        };
    }
}

PROVIDED_TEST("set sort")
{
    for (int i = 16; i <= 8 * 1024 * 1024; i = 2 * i)
    {
        BENCHMARK("execution time for array size " + std::to_string(i))
        {
            return count_operations(i, i, set_functor(), dont_normalize, false);
        };
    }
}

int main(int argc, char* argv[])
{
    // count operations
    std::cout << "unique and sort" << std::endl;
    count_operations(16, 8 * 1024 * 1024, unique_functor());

    std::cout << "set sort" << std::endl;
    count_operations(16, 8 * 1024 * 1024, set_functor());

    // now run benchmarks
    return Catch::Session().run(argc, argv);
}
