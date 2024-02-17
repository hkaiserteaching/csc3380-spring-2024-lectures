#pragma once

#include <concepts>

struct instrumented_base
{
    enum operations
    {
        n = 0,
        copy,
        assignment,
        destructor,
        default_constructor,
        equality,
        comparison,
        construction
    };

    static constexpr size_t number_ops = 8;

    static char const* counter_names[number_ops];
    static double counts[number_ops];

    static void initialize(size_t);
};

template <typename T>
    requires(std::semiregular<T> || std::regular<T> || std::totally_ordered<T>)
struct instrumented final : instrumented_base
{
    using value_type = T;

    T value;

    // Conversions from T and to T:
    instrumented(T const& x)
      : value(x)
    {
        ++counts[construction];
    }

    // Semiregular
    instrumented()
    {
        ++counts[default_constructor];
    }
    ~instrumented()
    {
        ++counts[destructor];
    }

    instrumented(instrumented const& x)
      : value(x.value)
    {
        ++counts[copy];
    }

    instrumented& operator=(instrumented const& x)
    {
        ++counts[assignment];
        value = x.value;
        return *this;
    }

    // Regular
    friend bool operator==(instrumented const& x, instrumented const& y)
    {
        ++counts[equality];
        return x.value == y.value;
    }
    friend bool operator!=(instrumented const& x, instrumented const& y)
    {
        return !(x == y);
    }

    // TotallyOrdered
    friend bool operator<(instrumented const& x, instrumented const& y)
    {
        ++counts[comparison];
        return x.value < y.value;
    }
    friend bool operator>(instrumented const& x, instrumented const& y)
    {
        return y < x;
    }
    friend bool operator<=(instrumented const& x, instrumented const& y)
    {
        return !(y < x);
    }
    friend bool operator>=(instrumented const& x, instrumented const& y)
    {
        return !(x < y);
    }
};
