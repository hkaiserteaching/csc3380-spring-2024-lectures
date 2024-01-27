#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

// Find the first element that equals a value
template <class In, class T>
In simple_find(In first, In last, T const& val)
{
    while (first != last && *first != val)
        ++first;
    return first;
}

// works for vector of ints
void f(std::vector<int> const& v, int x)
{
    auto p = simple_find(v.begin(), v.end(), x);
    if (p != v.end())    // did we find x?
    {
        std::cout << "Found x: " << *p << "\n";
    }
}

// works for list of strings
void f(std::list<std::string> const& v, std::string x)
{
    auto p = simple_find(v.begin(), v.end(), x);
    if (p != v.end())    // did we find x?
    {
        std::cout << "Found x: " << *p << "\n";
    }
}

// works of set of doubles
void f(std::set<double>& v, double x)
{
    auto p = simple_find(v.begin(), v.end(), x);
    if (p != v.end())    // did we find x?
    {
        std::cout << "Found x: " << *p << "\n";
    }
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    f(v, 5);

    std::list<std::string> l = {"1", "2", "3", "4", "5", "6", "7"};
    f(l, "5");

    std::set<double> s = {1., 2., 3., 4., 5., 6., 7.};
    f(s, 5.);
}