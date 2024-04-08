#include "Graph.h"            // graphical shapes
#include "Simple_window.h"    // stuff to deal with your system's windows

#include <iostream>
#include <memory>
#include <stdexcept>

void demo()
{
    // draw two lines:
    using namespace Graph_lib;

    Simple_window win(Point(100, 100), 600, 400, "16*16 color matrix");

    // normal vector, but imagine that it holds references to objects
    std::vector<std::unique_ptr<Graph_lib::Rectangle>> v;

    for (int i = 0; i < 16; ++i)    // i is the horizontal coordinate
    {
        for (int j = 0; j < 16; ++j)    // j is the vertical coordinate
        {
            v.push_back(std::make_unique<Graph_lib::Rectangle>(
                Point(i * 20, j * 20), 20, 20));
            v.back()->set_fill_color(i * 16 + j);
            win.attach(*v.back());
        }
    }

    win.wait_for_button();    // Draw!
}

int main()
try
{
    demo();    // the  main part of your code
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
