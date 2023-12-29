
#include <iostream>

// version 0
int multiply0(int n, int a)
{
    if (n == 1) return a;
    return multiply0(n - 1, a) + a;
}

// version 1
bool odd(int n) { return n & 1; }
int half(int n) { return n >> 1; }

int multiply1(int n, int a)
{
    if (n == 1) return a;
    int result = multiply1(half(n), a + a);
    if (odd(n)) result = result + a;
    return result;
}

// optimal multiply by 15
int multiply_by_15(int a)
{
    int b = (a + a) + a;    // 3 * a
    int c = b + b;          // 6 * a
    return (c + c) + b;     // 12 * a + 3 * a
}

// Multiply-accumulate, version 0
int mult_acc0(int r, int n, int a)
{
    if (n == 1) return r + a;
    if (odd(n))
    {
        return mult_acc0(r + a, half(n), a + a);
    }
    return mult_acc0(r, half(n), a + a);
}

// Multiply-accumulate, version 1
int mult_acc1(int r, int n, int a)
{
    if (n == 1) return r + a;
    if (odd(n)) r = r + a;
    return mult_acc1(r, half(n), a + a);
}

// Multiply-accumulate, version 2
int mult_acc2(int r, int n, int a)
{
    if (odd(n))
    {
        r = r + a;
        if (n == 1) return r;
    }
    return mult_acc2(r, half(n), a + a);
}

// Multiply-accumulate, version 3
int mult_acc3(int r, int n, int a)
{
    if (odd(n))
    {
        r = r + a;
        if (n == 1) return r;
    }
    n = half(n);
    a = a + a;
    return mult_acc3(r, n, a);
}

// Multiply-accumulate, version 4
int mult_acc4(int r, int n, int a)
{
    while(true) 
    {
        if (odd(n))
        {
            r = r + a;
            if (n == 1) return r;
        }
        n = half(n);
        a = a + a;
    }
}

// version 2
int multiply2(int n, int a)
{
    if (n == 1) return a;

    // Note: skip one iteration
    return mult_acc4(a, n - 1, a);
}

// version 3
int multiply3(int n, int a)
{
    while (!odd(n))
    {
        a = a + a;
        n = half(n);
    }

    if (n == 1) return a;
    return mult_acc4(a, n - 1, a);
}

// final version 4
int multiply4(int n, int a)
{
    while (!odd(n))
    {
        a = a + a;
        n = half(n);
    }

    if (n == 1) return a;

    // even(n - 1) ==> n - 1 != 1
    return mult_acc4(a, half(n - 1), a + a);
}

int main()
{
    std::cout << "multiply0: " << multiply0(41, 59) << "\n";
    std::cout << "multiply1: " << multiply1(41, 59) << "\n";

    std::cout << "mult_acc0: " << mult_acc0(0, 41, 59) << "\n";
    std::cout << "mult_acc1: " << mult_acc1(0, 41, 59) << "\n";
    std::cout << "mult_acc2: " << mult_acc2(0, 41, 59) << "\n";
    std::cout << "mult_acc3: " << mult_acc3(0, 41, 59) << "\n";
    std::cout << "mult_acc4: " << mult_acc4(0, 41, 59) << "\n";

    std::cout << "multiply2: " << multiply2(41, 59) << "\n";
    std::cout << "multiply3: " << multiply3(41, 59) << "\n";
    std::cout << "multiply4: " << multiply4(41, 59) << "\n";

    return 0;
}