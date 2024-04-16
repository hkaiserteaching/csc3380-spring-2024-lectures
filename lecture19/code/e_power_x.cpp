
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "Graph.h"            // graphical shapes
#include "Simple_window.h"    // stuff to deal with your system's windows

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

// factorial
double fac(int n)
{
    if (n <= 1)
        return 1;
    return fac(n - 1) * n;
}

double term(double x, int n)    // x^n/n!
{
    return std::pow(x, n) / fac(n);
}

double expe(double x, int n)    // sum of n terms of x
{
    double sum = 0;
    for (int i = 0; i < n; ++i)
        sum += term(x, i);
    return sum;
}

void demo()
{
    Simple_window win(Graph_lib::Point(100, 100), xmax, ymax,
        "Function graphing");    // make a window

    Graph_lib::Axis x(Graph_lib::Axis::x, Graph_lib::Point(20, y_orig), xlength,
        xlength / x_scale, "1 == 20 pixels");
    x.set_color(Graph_lib::Color::red);

    Graph_lib::Axis y(Graph_lib::Axis::y, Graph_lib::Point(x_orig, ymax - 20),
        ylength, ylength / y_scale, "1 == 20 pixels");
    y.set_color(Graph_lib::Color::red);

    win.attach(x);
    win.attach(y);

    Graph_lib::Function exp(std::exp, -15, 15, orig, 400, 20, 20);
    exp.set_color(Graph_lib::Color::blue);

    win.attach(exp);

    for (int n = 0; n < 40; ++n)
    {
        auto expN = [n](double x) { return expe(x, n); };

        Graph_lib::Function f(expN, -15, 15, orig, 400, 20, 20);
        f.set_color(Graph_lib::Color::black);

        win.set_label("exp approximation, x == " + std::to_string(n));
        win.attach(f);

        win.wait_for_button();    // Draw!

        win.detach(f);
    }
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
