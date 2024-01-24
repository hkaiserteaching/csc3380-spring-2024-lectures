#include <iostream>

// one concrete algorithm (doubles in array)
double sum(double array[], int n)
{
    double s = 0;
    for (int i = 0; i < n; ++i)
        s = s + array[i];
    return s;
}

// A more general STL-style code
// 'Iter' should be an Input_iterator
// 'T' should be something we can + and =, is the accumulator type
template <typename Iter, typename T>
T sum(Iter first, Iter last, T s)
{
    while (first != last)
    {
        s = s + *first;
        ++first;
    }
    return s;
}

int main()
{
    double a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double d1 = sum(a, std::size(a));
    std::cout << "concrete sum of {1, 2, 3, 4, 5, 6, 7, 8} == " << d1 << "\n";

    double d2 = sum(a, a + std::size(a), 0.0);
    std::cout << "generic sum of {1, 2, 3, 4, 5, 6, 7, 8} == " << d2 << "\n";

    return 0;
}
