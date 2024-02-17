#pragma once

#include <concepts>
#include <type_traits>

// T is Semiregular or Regular or TotallyOrdered
template <typename T>
    requires(std::semiregular<T> || std::regular<T> || std::totally_ordered<T>)
struct singleton final
{
    using value_type = T;
    T value;

    // Write conversions from T to singleton<T> and singleton<T> to T.
    explicit singleton(T const& x)
      : value(x)
    {
    }

    // Conversions from singleton<T> and to T:
    explicit operator T() const
    {
        return value;
    }

    template <typename U>
        requires(std::is_convertible_v<U, T>)
    singleton(singleton<U> const& x)
      : value(x.value)
    {
    }

    // Semiregular:
    singleton() = default;     // could be implicitly declared sometimes
    ~singleton() = default;    // could be implicitly declared

    // could be implicitly declared
    singleton(singleton const& x) = default;

    // could be implicitly declared
    singleton& operator=(singleton const& x) = default;

    // Regular
    friend bool operator==(singleton const& x, singleton const& y)
    {
        return x.value == y.value;
    }
    friend bool operator!=(singleton const& x, singleton const& y)
    {
        return !(x == y);
    }

    // TotallyOrdered
    friend bool operator<(singleton const& x, singleton const& y)
    {
        return x.value < y.value;
    }
    friend bool operator>(singleton const& x, singleton const& y)
    {
        return y < x;
    }
    friend bool operator<=(singleton const& x, singleton const& y)
    {
        return !(y < x);
    }
    friend bool operator>=(singleton const& x, singleton const& y)
    {
        return !(x < y);
    }
};
