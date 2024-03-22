
#include <algorithm>
#include <iostream>
#include <string>

bool is_palindrome(std::string const& s)
{
    return std::equal(s.begin(), s.end(), s.rbegin());
}

void report_is_palindrome(std::string const& s)
{
    bool b = is_palindrome(s);
    std::cout << s << " is" << (b ? "" : " not") << " a palindrome\n";
}

int main() {

    report_is_palindrome("racecar");
    report_is_palindrome("c++");

    return 0;
}