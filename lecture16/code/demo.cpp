// Getting access to the graphics system

#include "Graph.h"            // graphical shapes
#include "Simple_window.h"    // stuff to deal with your system's windows

void demo()
{
    ///////////////////////////////////////////////////////////////////////////
    // Demo 1

    // make a simple window

    // screen coordinate (100, 200) top left of window
    // window size(600*400)
    // title: Canvas
    Simple_window win(Graph_lib::Point(100, 100), 600, 400, "Canvas");

    win.wait_for_button();    // give control to the display engine

    ///////////////////////////////////////////////////////////////////////////
    // Demo 2

    // make an Axis
    // an axis is a kind of Shape
    // Axis::x means horizontal
    // starting at (20,300)
    // 280 pixels long
    // 10 "notches"
    // text "x axis"
    Graph_lib::Axis xa(
        Graph_lib::Axis::x, Graph_lib::Point(20, 300), 280, 10, "x axis");

    win.set_label("Canvas #2");
    win.attach(xa);           // attach axis xa to the window
    win.wait_for_button();    // give control to the display engine

    ///////////////////////////////////////////////////////////////////////////
    // Demo 3

    win.set_label("Canvas #3");

    Graph_lib::Axis ya(
        Graph_lib::Axis::y, Graph_lib::Point(20, 300), 280, 10, "y axis");
    ya.set_color(Graph_lib::Color::cyan);    // choose a color for the axis
    ya.label.set_color(
        Graph_lib::Color::dark_red);    // choose a color for the text

    win.attach(ya);
    win.wait_for_button();    // give control to the display engine

    ///////////////////////////////////////////////////////////////////////////
    // Demo 4

    win.set_label("Canvas #4");

    // plot sin() in the range [0:100)
    // with (0, 0) at (20, 150)
    // using 1000 points
    // scale x values * 50, scale y values * 50
    Graph_lib::Function sine(std::sin, 0, 100, Graph_lib::Point(20, 150), 1000,
        50, 50);    // sine curve

    win.attach(sine);
    win.wait_for_button();    // give control to the display engine

    ///////////////////////////////////////////////////////////////////////////
    // Demo 5

    win.set_label("Canvas #5");

    sine.set_color(
        Graph_lib::Color::blue);    // I changed my mind about sine's color

    Graph_lib::Polygon poly;    // a polygon, a Polygon is a kind of Shape
    poly.add(Graph_lib::Point(300, 200));    // three points makes a triangle
    poly.add(Graph_lib::Point(350, 100));
    poly.add(Graph_lib::Point(400, 200));

    poly.set_color(Graph_lib::Color::red);          // change the color
    poly.set_style(Graph_lib::Line_style::dash);    // change the line style

    win.attach(poly);
    win.wait_for_button();


    ///////////////////////////////////////////////////////////////////////////
    // Demo 6

    win.set_label("Canvas #6");

    // add a rectangular shape

    // at position 200, 200
    // of size 100*50
    Graph_lib::Rectangle r(Graph_lib::Point(200, 200), 100, 50);

    win.attach(r);
    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 6.1

    // Add a shape that looks like a rectangle
    win.set_label("Canvas #6.1");

    Graph_lib::Closed_polyline poly_rect;
    poly_rect.add(Graph_lib::Point(100, 50));
    poly_rect.add(Graph_lib::Point(200, 50));
    poly_rect.add(Graph_lib::Point(200, 100));
    poly_rect.add(Graph_lib::Point(100, 100));

    win.attach(poly_rect);
    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 6.2

    win.set_label("Canvas #6.2");
    poly_rect.add(Graph_lib::Point(50, 75));    // now poly_rect has 5 points

    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 7

    win.set_label("Canvas #7");

    // color the inside of the rectangle
    r.set_fill_color(Graph_lib::Color::yellow);

    // make the triangle contour fat and dashed
    poly.set_style(Graph_lib::Line_style(Graph_lib::Line_style::dash, 4));

    poly_rect.set_fill_color(Graph_lib::Color::green);
    poly_rect.set_style(Graph_lib::Line_style(Graph_lib::Line_style::dash, 2));

    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 8

    win.set_label("Canvas #8");

    // add text
    Graph_lib::Text t(Graph_lib::Point(100, 100), "Hello, graphical world!");

    win.attach(t);
    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 9

    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(20);

    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 10

    win.set_label("Canvas #10");

    Graph_lib::Image ii(
        Graph_lib::Point(100, 50), "image.gif");    // open an image file
    win.attach(ii);

    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 11

    win.set_label("Canvas #11");
    ii.move(100, 200);

    win.wait_for_button();

    ///////////////////////////////////////////////////////////////////////////
    // Demo 12

    win.set_label("Canvas #12");

    Graph_lib::Circle c(Graph_lib::Point(100, 200), 50);
    win.attach(c);

    Graph_lib::Ellipse e(Graph_lib::Point(100, 200), 75, 25);
    e.set_color(Graph_lib::Color::dark_red);
    win.attach(e);

    Graph_lib::Mark m(Graph_lib::Point(100, 200), 'x');
    win.attach(m);

    std::ostringstream oss;
    oss << "screen size: " << Graph_lib::x_max() << "*" << Graph_lib::y_max()
        << "; window size: " << win.x_max() << "*" << win.y_max();
    Graph_lib::Text sizes(Graph_lib::Point(100, 20), oss.str());
    win.attach(sizes);

    // 320*240 pixel gif
    Graph_lib::Image cal(Graph_lib::Point(225, 225), "snow_cpp.gif");

    // display center of image
    cal.set_mask(Graph_lib::Point(40, 40), 200, 150);
    win.attach(cal);

    win.wait_for_button();
}

int main()
try
{
    demo();    // the  main part of your code
    return 0;
}
catch (std::exception& e)
{
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Some exception\n";
    return 2;
}
