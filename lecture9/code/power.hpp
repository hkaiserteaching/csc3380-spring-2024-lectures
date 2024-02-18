
#pragma once

#include <concepts>
#include <functional>
#include <type_traits>

// check whether a given type is regular
template <typename T>
concept Regular = std::regular<T>;

// "the expression a+b is a valid expression that will compile"
template <typename T>
concept Addable = requires(T a, T b) { a + b; };

template <typename T>
concept HasAdditiveIdentity = requires(T) { T(0); };

template <typename T>
concept AdditiveIsInvertible = requires(T a) { -a; };

template <typename T>
concept NoncommutativeAdditiveSemigroup = Regular<T> && Addable<T>;

template <typename T>
concept NoncommutativeAdditiveMonoid =
    NoncommutativeAdditiveSemigroup<T> && HasAdditiveIdentity<T>;

template <typename T>
concept NoncommutativeAdditiveGroup =
    NoncommutativeAdditiveMonoid<T> && AdditiveIsInvertible<T>;

// the additive identity is zero
template <typename T>
    requires(NoncommutativeAdditiveMonoid<T>)
T identity_element(std::plus<T>)
{
    return T(0);
}

// the additive inverse operation is negate
template <typename T>
    requires(NoncommutativeAdditiveGroup<T>)
auto inverse_operation(std::plus<T>)
{
    return std::negate<T>();
}

// "the expression a*b is a valid expression that will compile"
template <typename T>
concept Multipliable = requires(T a, T b) { a* b; };

template <typename T>
concept HasMultiplicativeIdentity = requires(T) { T(1); };

template <typename T>
concept MultiplicativeIsInvertible = requires(T a) { T(1) / a; };

template <typename T>
concept MultiplicativeSemigroup = std::regular<T> && Multipliable<T>;

template <typename T>
concept MultiplicativeMonoid =
    MultiplicativeSemigroup<T> && HasMultiplicativeIdentity<T>;

template <typename T>
concept MultiplicativeGroup =
    MultiplicativeMonoid<T> && MultiplicativeIsInvertible<T>;

// the multiplicative identity is one
template <typename T>
    requires(MultiplicativeMonoid<T>)
T identity_element(std::multiplies<T>)
{
    return T(1);
}

// the multiplicative inverse is reciprocal
template <typename T>
    requires(MultiplicativeGroup<T>)
struct reciprocal
{
    T operator()(T x) const
    {
        return T(1) / x;
    }
};

template <typename T>
    requires(MultiplicativeGroup<T>)
auto inverse_operation(std::multiplies<T>)
{
    return reciprocal<T>();
}

// check whether a given type is an integral type
template <typename T>
concept Integer = std::integral<T>;

// check whether the domain of a given operation is the same as its argument
template <typename Op, typename A>
concept Domain = std::same_as<std::invoke_result_t<Op, A, A>, A>;

// we can't check whether Op is associative, assume true
template <typename Op>
concept SemigroupOperation = true;

template <typename Op>
concept OperationHasIdentityElement = requires(Op op) { identity_element(op); };

template <typename Op>
concept OperationHasInverse = requires(Op op) { inverse_operation(op); };

template <typename Op>
concept MonoidOperation =
    SemigroupOperation<Op> && OperationHasIdentityElement<Op>;

template <typename Op>
concept GroupOperation = MonoidOperation<Op> && OperationHasInverse<Op>;

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

template <typename A, typename N, typename Op>
    requires(
        Regular<A> && Integer<N> && SemigroupOperation<Op> && Domain<Op, A>)
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
    // precondition: n >= 0
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r = op(r, a);
            if (n == 1)
                return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

template <typename A, typename N, typename Op>
    requires(
        Regular<A> && Integer<N> && SemigroupOperation<Op> && Domain<Op, A>)
A power_semigroup(A a, N n, Op op)
{
    // precondition: n > 0
    while (!odd(n))
    {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1)
        return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <typename A, typename N, typename Op>
    requires(Regular<A> && Integer<N> && MonoidOperation<Op> && Domain<Op, A>)
A power_monoid(A a, N n, Op op)
{
    // precondition: n >= 0
    if (n == 0)
        return identity_element(op);
    return power_semigroup(a, n, op);
}

template <typename A, typename N, typename Op>
    requires(Regular<A> && Integer<N> && GroupOperation<Op> && Domain<Op, A>)
A power_group(A a, N n, Op op)
{
    // precondition: none
    if (n < 0)
    {
        n = -n;
        a = inverse_operation(op)(a);
    }
    return power_monoid(a, n, op);
}
