#include <concepts>
#include <functional>

template <typename T, typename Compare>
    requires(std::strict_weak_order<Compare, T, T>)
void sort2(T& a, T& b, Compare cmp)
{
    if (cmp(b, a))
    {
        swap(a, b);
    }
}

template <typename T, typename Compare>
    requires(std::strict_weak_order<Compare, T, T>)
T const& max(T const& a, T const& b, Compare cmp)
{
    if (cmp(b, a))
    {
        return a;
    }
    return b;
}

template <std::totally_ordered T>
T const& max(T const& a, T const& b)
{
    return max(a, b, std::less<T>());    // std::less<T>() is an object
}
