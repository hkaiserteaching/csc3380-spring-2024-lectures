#include "Graph.h"            // graphical shapes
#include "Simple_window.h"    // stuff to deal with your system's windows

#include <iostream>
#include <stdexcept>

void demo()
{
    // draw two lines:
    using namespace Graph_lib;

    Simple_window win(Point(100, 100), 600, 400, "Canvas");    // make a window

    Lines x;
    x.add(Point(100, 100), Point(200, 100));    // horizontal line
    x.add(Point(150, 50), Point(150, 150));     // vertical line

    win.attach(x);            // attach Lines x to Window win
    win.wait_for_button();    // Draw!

    win.detach(x);

    int x_size = win.x_max();
    int y_size = win.y_max();
    int x_grid = 80;
    int y_grid = 40;
    
    Lines grid;
    for (int x = x_grid; x < x_size; x += x_grid)    // vertical lines
        grid.add(Point(x, 0), Point(x, y_size));
    for (int y = y_grid; y < y_size; y += y_grid)    // horizontal lines
        grid.add(Point(0, y), Point(x_size, y));

    // attach our grid to our window (note 'grid' is one object)
    win.attach(grid);

    win.wait_for_button();    // Draw!

    grid.set_color(Color::red);
    win.wait_for_button();    // Draw!

    grid.set_style(Line_style(Line_style::dash, 2));
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
