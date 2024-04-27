#include <iostream>
#include <string>
#include <vector>

int const data_size = 10000;

std::string program = R"(

)";

void bf_interpreter()
{
}

int main()
try
{
    bf_interpreter();
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    std::cerr << "Some exception\n";
    return 2;
}
