// Getting access to the graphics system
#include "Graph.h"            // graphical shapes
#include "Simple_window.h"    // stuff to deal with your system's windows

int main()
{
    Graph_lib::Point tl(100, 200);    // a point (obviously)

    // screen coordinate (100, 200) top left of window
    // window size(600*400)
    // title: Canvas
    Simple_window win(tl, 600, 400, "Canvas");    // make a simple window

    Graph_lib::Polygon poly;    // make a shape (a polygon, obviously)

    poly.add(Graph_lib::Point(300, 200));    // add three points
    poly.add(Graph_lib::Point(350, 100));
    poly.add(Graph_lib::Point(400, 200));

    poly.set_color(
        Graph_lib::Color::red);    // make the polygon red (obviously)

    win.attach(poly);    // connect poly to the window

    win.wait_for_button();    // give control to the display engine
}
