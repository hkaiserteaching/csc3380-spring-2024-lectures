
#include <iostream>

#include "power.hpp"

int main()
{
    auto semigroup_result =
        power_semigroup(42.8, 23, std::multiplies<double>());
    std::cout << "power_semigroup: " << semigroup_result << '\n';

    auto monoid_result = power_monoid(42.8, 0, std::plus<double>());
    std::cout << "power_monoid: " << monoid_result << '\n';

    auto group_result = power_group(42.8, -24, std::multiplies<double>());
    std::cout << "power_group: " << group_result << '\n';
}