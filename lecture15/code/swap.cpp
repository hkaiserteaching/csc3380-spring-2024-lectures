
#include <concepts>
#include <iostream>
#include <utility>
#include <vector>

template <std::semiregular T>
void swap_copy(T& a, T& b)
{
    T tmp(a);
    a = b;
    b = tmp;
}

template <std::semiregular T>
void swap(std::vector<T>& a, std::vector<T>& b)
{
    // swap headers of a and b
    // fix back pointers (for things like linked lists)
}

template <std::unsigned_integral T>
void swap_xor(T& a, T& b)
{
    // if a is identical to b the result is always 0
    if (&a != &b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
}

template <std::semiregular T>
void swap(T& a, T& b)
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

int main()
{
    int a = 42, b = 43;
    swap_copy(a, b);
    std::cout << "a: " << a << ", b: " << b << "\n";    // a: 43, b: 42

    unsigned int c = 42, d = 43;
    swap_xor(c, d);
    std::cout << "c: " << c << ", d: " << d << "\n";    // c: 43, d: 42

    return 0;
}
