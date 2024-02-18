
#include <concepts>
#include <iostream>

template <typename T>
concept Multipliable = requires(T a, T b) {
    a * b;    // "the expression a*b is a valid expression that will compile"
};

template <typename T>
concept HasMultiplicativeIdentity = requires(T) { T(1); };

template <typename T>
concept MultiplicativeIsInvertible = requires(T a) { T(1) / a; };

template <typename T>
concept MultiplicativeSemigroup = std::regular<T> && Multipliable<T>;

template <typename T>
concept MultiplicativeMonoid = MultiplicativeSemigroup<T> && HasMultiplicativeIdentity<T>;

template <typename T>
concept MultiplicativeGroup = MultiplicativeMonoid<T> && MultiplicativeIsInvertible<T>;

template <typename T>
concept Integer = std::integral<T>;

template <Integer N>
bool odd(N n)
{
    return bool(n & 0x1);
}

template <Integer N>
N half(N n)
{
    return n >> 1;
}

template <MultiplicativeSemigroup A, Integer N>
A power_accumulate_semigroup(A r, A a, N n)
{
    // precondition: n >= 0
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r = r * a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a = a * a;
    }
}

template <MultiplicativeSemigroup A, Integer N>
A power_semigroup(A a, N n)
{
    // precondition: n > 0
    while (!odd(n))
    {
        a = a * a;
        n = half(n);
    }
    if (n == 1)
        return a;
    return power_accumulate_semigroup(a, a * a, half(n - 1));
}

template <MultiplicativeMonoid A, Integer N>
A power_monoid(A a, N n)
{
    // precondition: n >= 0
    if (n == 0)
        return A(1);
    return power_semigroup(a, n);
}

template <MultiplicativeGroup A>
A multiplicative_inverse(A a)
{
    return A(1) / a;
}

template <MultiplicativeGroup A, Integer N>
A power_group(A a, N n)
{
    // precondition: none
    if (n < 0)
    {
        n = -n;
        a = multiplicative_inverse(a);
    }
    return power_monoid(a, n);
}

int main()
{
    auto semigroup_result = power_semigroup(42.8, 23);
    std::cout << "power_semigroup: " << semigroup_result << '\n';

    auto monoid_result = power_monoid(42.8, 0);
    std::cout << "power_monoid: " << monoid_result << '\n';

    auto group_result = power_group(42.8, -24);
    std::cout << "power_group: " << group_result << '\n';
}
