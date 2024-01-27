
#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename In, typename Pred>
In my_find_if(In first, In last, Pred pred)
{
    while (first != last && !pred(*first))
        ++first;
    return first;
}

bool odd_f(int i)
{
    return i % 2;   // % is the remainder
}    

struct Odd
{
    bool operator()(int i) const { return i % 2; }
};

Odd odd_fo;    // make an object odd of type Odd

auto odd_l = [](int i) { return i % 2; };

void f(std::vector<int>& v)
{
    auto p_f = my_find_if(v.begin(), v.end(), odd_f);
    if (p_f != v.end())
        std::cout << "we found an odd number using the function odd_f\n";

    auto p_fo = my_find_if(v.begin(), v.end(), odd_fo);
    if (p_fo != v.end())
        std::cout << "we found an odd number using the function object odd_fo\n";

    auto p_l = my_find_if(v.begin(), v.end(), odd_l);
    if (p_l != v.end())
        std::cout << "we found an odd number using the lambda odd_l\n";
}

template <typename T>
struct less_than
{
    T val;    // value to compare with

    less_than(T x)
      : val(x)
    {
    }

    bool operator()(T const& x) const
    {
        return x < val;
    }
};

struct record
{
    std::string name;    // standard string for ease of use
    char addr[24];       // old C-style string to match database layout
    // ...
};

// Different comparisons for record objects:
struct cmp_by_name
{
    bool operator()(record const& a, record const& b) const
    {
        return a.name < b.name; // look at the name field of Rec
    }    
};

struct cmp_by_addr
{
    bool operator()(record const& a, record const& b) const
    {
        return 0 < std::strncmp(a.addr, b.addr, 24);    // correct?
    }    
};
// note how the comparison function objects are used to hide ugly
// and error-prone code 

int main()
{
    // find x < 43 in vector<int> :
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    auto p = my_find_if(v.begin(), v.end(), less_than(43));
    if (p != v.end())
        std::cout << "we found a number smaller than 43\n";

    // find x < “perfection” in list<string>:
    std::list<std::string> ls = {"abc", "def", "perfection"};
    auto q = my_find_if(ls.begin(), ls.end(), less_than("perfection"));
    if (q != ls.end())
        std::cout << "we found a string 'smaller' than 'perfection'\n";

    std::vector<record> vr = {
        {"John Doe", "123 3rd Avenue"},
        {"Donald Duck", "42 Main Street"},
    };

    std::sort(vr.begin(), vr.end(), cmp_by_name());    // sort by name
    std::sort(vr.begin(), vr.end(), cmp_by_addr());    // sort by addr

    return 0;
}
