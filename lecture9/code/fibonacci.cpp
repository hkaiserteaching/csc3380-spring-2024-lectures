#include <iostream>
#include <utility>

int fib(int n)
{
    if (n == 0)
        return 0;
        
    std::pair<int, int> v = {0, 1};
    for (int i = 0; i < n - 1; i++)
    {
        v = {v.second, v.first + v.second};
    }
    return v.first;
}

int main()
{
    int num;
    std::cout << "Enter the number : ";
    std::cin >> num;
    std::cout << "\nThe fibonacci number : " << fib(num) << '\n';
    return 0;
}
