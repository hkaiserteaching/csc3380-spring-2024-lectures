
#include "Simple_window.h"

#include <string>

//------------------------------------------------------------------------------

Simple_window::Simple_window(Graph_lib::Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    next_button(Graph_lib::Point{x_max()-70,0}, 70, 20, "Next", cb_next),
    button_pushed(false)
{
    attach(next_button);
}

//------------------------------------------------------------------------------
void Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    // Simpler handler
    while (!button_pushed) 
	    Fl::wait();
    button_pushed = false;
    Fl::redraw();
}

//------------------------------------------------------------------------------

void Simple_window::cb_next(Graph_lib::Address, Graph_lib::Address pw)
// call Simple_window::next() for the window located at pw
{  
    Graph_lib::reference_to<Simple_window>(pw).next();    
}

//------------------------------------------------------------------------------

void Simple_window::next()
{
    button_pushed = true;
}

//------------------------------------------------------------------------------
