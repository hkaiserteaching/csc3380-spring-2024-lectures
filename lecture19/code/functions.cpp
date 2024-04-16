#include "Graph.h"            // graphical shapes
#include "Simple_window.h"    // stuff to deal with your system's windows

#include <iostream>
#include <stdexcept>

// y == 1
double one(double)
{
    return 1;
}

// y == x/2
double slope(double x)
{
    return x / 2;
}

// y == x*x
double square(double x)
{
    return x * x;
}

#include <cmath>    // standard mathematical functions

// You can combine functions (e.g., by addition):
double sloping_cos(double x)
{
    return std::cos(x) + slope(x);
}

const int xmax = 600;    // window size
const int ymax = 400;

const int x_orig = xmax / 2;
const int y_orig = ymax / 2;
const Graph_lib::Point orig(x_orig, y_orig);    // position of (0, 0) in window

const int r_min = -10;    // range [-10:11) == [-10:10] of x
const int r_max = 11;

const int n_points = 400;    // number of points used in range

const int x_scale = 20;    // scaling factors
const int y_scale = 20;

const int xlength = xmax - 40;    // axis length
const int ylength = ymax - 40;

// Choosing a center (0,0), scales, and number of points can be fiddly
// The range usually comes from the definition of what you are doing

void demo()
{
    Simple_window win(Graph_lib::Point(100, 100), xmax, ymax,
        "Function graphing");    // make a window

    Graph_lib::Function s(one, -10, 11, orig, n_points, x_scale, y_scale);
    Graph_lib::Function s2(slope, -10, 11, orig, n_points, x_scale, y_scale);
    Graph_lib::Function s3(square, -10, 11, orig, n_points, x_scale, y_scale);

    s.set_color(Graph_lib::Color::black);
    s2.set_color(Graph_lib::Color::black);
    s3.set_color(Graph_lib::Color::black);

    win.attach(s);     // attach Function s to Window win
    win.attach(s2);    // attach Function s2 to Window win
    win.attach(s3);    // attach Function s3 to Window win

    win.wait_for_button();    // Draw!

    Graph_lib::Text ts(Graph_lib::Point(100, y_orig - 30), "one");
    Graph_lib::Text ts2(Graph_lib::Point(100, y_orig + y_orig / 2 - 10), "x/2");
    Graph_lib::Text ts3(Graph_lib::Point(x_orig - 90, 20), "x*x");

    win.attach(ts);     // attach Text ts to Window win
    win.attach(ts2);    // attach Text ts2 to Window win
    win.attach(ts3);    // attach Text ts3 to Window win

    win.wait_for_button();    // Draw!

    Graph_lib::Axis x(Graph_lib::Axis::x, Graph_lib::Point(20, y_orig), xlength,
        xlength / x_scale, "1 == 20 pixels");
    Graph_lib::Axis y(Graph_lib::Axis::y, Graph_lib::Point(x_orig, ymax - 20),
        ylength, ylength / y_scale, "1 == 20 pixels");

    win.attach(x);
    win.attach(y);

    win.wait_for_button();    // Draw!

    s.set_color(Graph_lib::Color::green);
    ts.set_color(Graph_lib::Color::green);

    x.set_color(Graph_lib::Color::red);
    y.set_color(Graph_lib::Color::red);

    win.wait_for_button();    // Draw!

    Graph_lib::Function s4(std::cos, -10, 11, orig, 400, 20, 20);
    s4.set_color(Graph_lib::Color::blue);

    Graph_lib::Function s5(sloping_cos, -10, 11, orig, 400, 20, 20);

    win.attach(s4);
    win.attach(s5);

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
