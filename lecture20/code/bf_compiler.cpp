// Brainfuck (bf) compiler

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string prefix = R"(

#include <iostream>
#include <vector>

int const data_size = 10000;

void bf_execution()
{
    std::vector<char> data(data_size, 0);
    auto curr_cell = data.begin();

)";

std::string suffix = R"(
}

int main()
try
{
    bf_execution();
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
)";

std::string program = R"(

)";

void bf_compiler()
{
    std::ofstream out("../../code/bf_code.cpp");

}

int main()
try
{
    bf_compiler();
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
