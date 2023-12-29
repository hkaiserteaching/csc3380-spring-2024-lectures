#include <algorithm>
#include <iostream>
#include <set>

int main()
{
    int a[] = {1, 3, 1, 4, 1, 5};

    std::set<int> set_of_ints(a, a + std::size(a));
    std::cout << set_of_ints.size() << std::endl;

    std::sort(a, a + std::size(a));
    std::cout << std::unique(a, a + std::size(a)) - a << std::endl;

    return 0;
}
