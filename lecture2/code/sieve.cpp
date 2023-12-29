#include <algorithm>
#include <concepts>
#include <iostream>

template <typename I, typename N>
    requires(std::random_access_iterator<I> && std::integral<N>)
void mark_sieve(I first, I last, N factor)
{
    // precondition: range [first, last) is not empty
    // assert(first != last)

    *first = false;    // cross out first non-prime
    while (last - first > factor)
    {
        first = first + factor;
        *first = false;    // cross out first non-prime
    }
}

template <typename I, typename N>
    requires(std::random_access_iterator<I> && std::integral<N>)
void sift0(I first, N n)
{
    std::fill(first, first + n, true);
    N i = 0;
    N index_square = 3;
    while (index_square < n)
    {
        // invariant: index_square = 2 * i^2 + 6*i + 3
        if (first[i])
        {
            // candidate is prime
            mark_sieve(first + index_square, first + n, i + i + 3);
        }
        ++i;
        index_square = 2 * i * (i + 3) + 3;
    }
}

template <typename I, typename N>
    requires(std::random_access_iterator<I> && std::integral<N>)
void sift(I first, N n)
{
    I last = first + n;
    std::fill(first, last, true);
    N i = 0;
    N index_square = 3;
    N factor = 3;
    while (index_square < n)
    {
        // invariant: index_square = 2 * i^2 + 6*i + 3
        if (first[i])
        {
            // candidate is prime
            mark_sieve(first + index_square, last, factor);
        }
        ++i;

        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}

template <typename I, typename N>
    requires(std::random_access_iterator<I> && std::integral<N>)
void print_primes(I first, N size)
{
    std::cout << "1 2";
    for (int i = 0; i < size; ++i)
    {
        if (first[i])
        {
            std::cout << " " << 2 * i + 3;
        }
    }
    std::cout << std::endl;
}

int main()
{
    constexpr int m = 53;
    constexpr int size = (m - 3) / 2;

    bool is_prime[size];

    sift0(is_prime, size);
    print_primes(is_prime, size);

    sift(is_prime, size);
    print_primes(is_prime, size);

    return 0;
}