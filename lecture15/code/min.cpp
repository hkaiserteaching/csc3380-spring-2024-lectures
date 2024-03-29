#include <concepts>
#include <functional>

template <std::totally_ordered T>
T const& min_incorrect(T const& a, T const& b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

template <typename T, typename Compare>
T const& min_correct(T const& a, T const& b, Compare cmp)
{
    if (cmp(b, a))
    {
        return b;
    }
    else
    {
        return a;
    }
}

template <std::totally_ordered T>
struct less
{
    bool operator()(T const& a, T const& b) const
    {
        return a < b;
    }
};

template <std::totally_ordered T>
T const& min_correct(T const& a, T const& b)
{
    return min_correct(a, b, less<T>());    // std::less<T>() is an object
}
