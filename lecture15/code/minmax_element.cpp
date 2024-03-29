#include <algorithm>
#include <concepts>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

template <std::forward_iterator I, typename Compare>
    requires(std::strict_weak_order<Compare, std::iter_value_t<I>,
        std::iter_value_t<I>>)
std::pair<I, I> minmax_element(I first, I last, Compare cmp)
{
    // handle empty sequence
    if (first == last)
    {
        return std::make_pair(last, last);
    }

    // handle sequence with one element
    I min_el = first;
    ++first;
    if (first == last)
    {
        return std::make_pair(min_el, min_el);
    }

    // initialize running min and max
    I max_el = first;
    I next = first;
    ++next;

    if (cmp(*max_el, *min_el))
    {
        std::swap(min_el, max_el);
    }

    // loop over elements updating min and max
    while (first != last && next != last)
    {
        // next and first are the next pair of elements to examine
        I potential_min = first;
        I potential_max = next;

        if (cmp(*potential_max, *potential_min))
        {
            std::swap(potential_max, potential_min);
        }

        if (cmp(*potential_min, *min_el))
        {
            min_el = potential_min;
        }

        if (!cmp(*potential_max, *max_el))
        {
            max_el = potential_max;
        }

        ++next;
        first = next;
        ++next;
    }

    // handle possible leftover element
    if (first != last)
    {
        // odd elements, one left over
        if (cmp(*first, *min_el))
        {
            min_el = first;
            // first < min_el <= max_el, so we don't need to check the next case
        }
        else if (!cmp(*first, *max_el))
        {
            max_el = first;
        }
    }

    return std::make_pair(min_el, max_el);
}

template <std::forward_iterator I, typename Compare>
    requires(std::strict_weak_order<Compare, std::iter_value_t<I>,
        std::iter_value_t<I>>)
I min_element(I first, I last, Compare cmp)
{
    if (first == last)
    {
        return last;
    }

    I min_el = first;
    ++first;

    while (first != last)
    {
        if (cmp(*first, *min_el))
        {
            min_el = first;
        }
        ++first;
    }

    return min_el;
}

template <std::forward_iterator I, typename Compare>
    requires(std::strict_weak_order<Compare, std::iter_value_t<I>,
        std::iter_value_t<I>>)
I max_element(I first, I last, Compare cmp)
{
    if (first == last)
        return last;
    I max_el = first;
    while (++first != last)
    {
        if (!cmp(*first, *max_el))
        {
            max_el = first;
        }
    }
    return max_el;
}

template <std::forward_iterator I, typename Compare>
    requires(std::strict_weak_order<Compare, std::iter_value_t<I>,
        std::iter_value_t<I>>)
std::pair<I, I> minmax_element_simple(I first, I last, Compare comp)
{
    return std::make_pair(
        ::min_element(first, last, comp), ::max_element(first, last, comp));
}

double comparisons = 0;

struct counting_compare
{
    template <typename T>
    bool operator()(const T& x, const T& y) const
    {
        ++comparisons;
        return x < y;
    }
};

counting_compare counting_less;

template <typename I>
std::pair<double, double> minmax_comparisons(I first, I last)
{
    typedef typename std::iterator_traits<I>::value_type T;
    std::pair<double, double> result;
    std::pair<I, I> m0, m1;

    std::vector<T> seq(first, last);
    {
        comparisons = 0;
        m0 = ::minmax_element_simple(seq.begin(), seq.end(), counting_less);
        result.first = comparisons;
    }
    {
        comparisons = 0;
        m1 = ::minmax_element(seq.begin(), seq.end(), counting_less);
        result.second = comparisons;
    }
    if (m0 != m1)
    {
        std::cout << "Failed: different mins or maxs\n";
    }
    return result;
}

template <typename I>
std::pair<double, double> minmax_times(I first, I last, size_t iterations)
{
    typedef typename std::iterator_traits<I>::value_type T;
    typedef typename std::iterator_traits<I>::difference_type N;

    N n = std::distance(first, last);
    std::pair<double, double> result;
    std::pair<I, I> m0, m1;
    double time;
    double nanoseconds = 1000000000.0 / double(CLOCKS_PER_SEC);
    std::vector<T> seq(iterations * n);

    for (N i(0); i < iterations; ++i)
        std::copy(first, last, seq.begin() + i * n);

    time = clock();
    for (N i(0); i < iterations; ++i)
    {
        m0 = ::minmax_element_simple(
            seq.begin() + i * n, seq.begin() + (i + 1) * n, std::less<T>());
    }
    time = clock() - time;

    result.first = (time * nanoseconds) / double(iterations);
    for (N i(0); i < iterations; ++i)
        std::copy(first, last, seq.begin() + i * n);

    time = clock();
    for (size_t i(0); i < iterations; ++i)
    {
        m1 = ::minmax_element(
            seq.begin() + i * n, seq.begin() + (i + 1) * n, std::less<T>());
    }
    time = clock() - time;
    result.second = (time * nanoseconds) / double(iterations);

    if (m0 != m1)
        std::cout << "Failed: different mins or maxs\n";
    return result;
}

void print_comparisons(size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Comparisons\n"
              << "\tn\t      minmax_simple\tminmax\t  gain (%)\t\n";
    for (size_t i(64); i < n; i <<= 1)
    {
        std::vector<uint64_t> buffer(i);
        std::iota(buffer.begin(), buffer.end(), std::uint64_t(0));
        std::shuffle(buffer.begin(), buffer.end(), gen);
        std::pair<double, double> result =
            minmax_comparisons(buffer.begin(), buffer.end());

        std::cout << std::setw(9) << i << std::fixed << std::setprecision(2)
                  << "\t\t" << result.first / i << "\t\t" << result.second / i
                  << "\t\t" << std::setprecision(0)
                  << (1 - result.second / result.first) * 100 << std::endl;
    }
}

template <typename T>
void print_times(size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "\nTimes\n"
              << "\tn\t      minmax_simple\tminmax\t  gain (%)\t\n";
    for (size_t i(64); i < n; i <<= 1)
    {
        std::vector<T> buffer(i);
        std::iota(buffer.begin(), buffer.end(), T(0));
        std::shuffle(buffer.begin(), buffer.end(), gen);
        std::pair<double, double> result =
            minmax_times(buffer.begin(), buffer.end(), n / i);

        std::cout << std::setw(9) << i << std::fixed << std::setprecision(2)
                  << "\t\t" << result.first / i << "\t\t" << result.second / i
                  << "\t\t" << std::setprecision(0)
                  << (1 - result.second / result.first) * 100 << std::endl;
    }
}

int main()
{
    print_comparisons(128 * 1024 * 1024);
    print_times<std::uint64_t>(128 * 1024 * 1024);
}
