
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

struct X
{
    int64_t value;
};

std::ostream& operator<<(std::ostream& out, X const& el)
{
    return out << el.value;
}

std::istream& operator>>(std::istream& in, X& el)
{
    return in >> el.value;
}

void custom_type_io()
{
    {
        std::ofstream out("data.txt");

        X a{42};
        X b{7};
        out << a << " " << b;
    }    // out closes

    {
        std::ifstream in("data.txt");

        X a{0};
        X b{0};
        in >> a >> b;

        std::cout << "a.value == " << a << ", b.value == " << b
                  << "\n";    // a.value == 42, b.value == 7
    }
}

void file_io()
{
    {
        // Open for writing or create if file doesn't exist.
        std::ofstream out("data.txt");
        out << "Hello World!\n";
    }    // out closes

    {
        // Open for reading.
        std::ifstream in("data.txt");

        std::string line;
        std::getline(in, line);

        std::cout << "line == " << line << "\n";    // line == "Hello World!"
    }
}

void string_io()
{
    std::string line;

    {
        std::stringstream strm;
        strm << "Hello world!";
        line = strm.str();
    }

    std::cout << "line == " << line << "\n";    // line == "Hello World!"
}

int main()
{
    file_io();
    custom_type_io();
}
