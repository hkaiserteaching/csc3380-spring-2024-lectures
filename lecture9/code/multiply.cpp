
#include <concepts>
#include <iostream>

template <typename T>
concept Addable = requires(T a, T b) {
    a + b;    // "the expression a+b is a valid expression that will compile"
};

template <typename T>
concept HasAdditiveIdentity = requires(T) { T(0); };

template <typename T>
concept AdditiveIsInvertible = requires(T a) { 1 / a; };

template <typename T>
concept NoncommutativeAdditiveSemigroup = std::regular<T> && Addable<T>;

template <typename T>
concept NoncommutativeAdditiveMonoid =
    NoncommutativeAdditiveSemigroup<T> && HasAdditiveIdentity<T>;

template <typename T>
concept NoncommutativeAdditiveGroup =
    NoncommutativeAdditiveMonoid<T> && AdditiveIsInvertible<T>;

template <typename T>
concept Integer = std::integral<T>;

template <typename N>
    requires(Integer<N>)
bool odd(N n)
{
    return bool(n & 0x1);
}

template <typename N>
    requires(Integer<N>)
N half(N n)
{
    return n >> 1;
}

template <typename A, typename N>
    requires(NoncommutativeAdditiveSemigroup<A> && Integer<N>)
A multiply_accumulate_semigroup(A r, N n, A a)
{
    // precondition: n >= 0
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r = r + a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a = a + a;
    }
}

template <typename A, typename N>
    requires(NoncommutativeAdditiveSemigroup<A> && Integer<N>)
A multiply_semigroup(N n, A a)
{
    // precondition: n > 0
    while (!odd(n))
    {
        a = a + a;
        n = half(n);
    }
    if (n == 1)
        return a;
    return multiply_accumulate_semigroup(a, half(n - 1), a + a);
}

template <typename A, typename N>
    requires(NoncommutativeAdditiveMonoid<A> && Integer<N>)
A multiply_monoid(N n, A a)
{
    // precondition: n >= 0
    if (n == 0)
        return A(0);
    return multiply_semigroup(n, a);
}

template <typename A, typename N>
    requires(NoncommutativeAdditiveMonoid<A> && Integer<N>)
A multiply_group(N n, A a)
{
    // precondition: none
    if (n < 0)
    {
        n = -n;
        a = -a;
    }
    return multiply_monoid(n, a);
}

int main()
{
    auto semigroup_result = multiply_semigroup(23, 42.8);
    std::cout << "multiply_semigroup: " << semigroup_result << '\n';

    auto monoid_result = multiply_monoid(0, 42.8);
    std::cout << "multiply_monoid: " << monoid_result << '\n';

    auto group_result = multiply_group(-24, 42.8);
    std::cout << "multiply_group: " << group_result << '\n';
}
