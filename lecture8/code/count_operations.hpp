#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <numeric>
#include <random>
#include <vector>

#include "instrumented.hpp"
#include "table_util.hpp"

double normalized_by_n(double x, double n)
{
    return x / n;
}

double normalized_by_nlogn(double x, double n)
{
    return x / (n * (log(n) / log(2)));
}

double normalized_by_nlogn1(double x, double n)
{
    return x / (n * log(n) - n);
}

double dont_normalize(double x, double)
{
    return x;
}

template <typename Function>
std::size_t count_operations(std::size_t i, std::size_t j, Function fun,
    double (*norm)(double, double) = dont_normalize, bool print = true)
{
    // measure operations on an interval of a given length
    // ranging from i to j and going through i, 2i, 4i, ... up to and including j

    constexpr std::size_t cols = instrumented<double>::number_ops;

    std::size_t decimals[cols];
    decimals[0] = 0;

    std::size_t normalized((norm == dont_normalize) ? 0 : 2);

    std::fill(decimals + 1, decimals + cols, normalized);

    table_util table;
    if (print)
    {
        table.print_headers(instrumented<double>::counter_names,
            instrumented<double>::number_ops, 12);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    while (i <= j)
    {
        instrumented<double>::initialize(i);

        {
            std::vector<instrumented<double>> vec(i);
            std::iota(vec.begin(), vec.end(), 0.0);
            std::shuffle(vec.begin(), vec.end(), gen);

            fun(vec.begin(), vec.end());
        }

        double* count_p = instrumented<double>::counts;

        for (std::size_t k(1); k < cols; ++k)
            count_p[k] = norm(count_p[k], count_p[0]);

        if (print)
        {
            table.print_row(count_p, decimals);
        }

        i *= 2;
    }

    return i;
}
