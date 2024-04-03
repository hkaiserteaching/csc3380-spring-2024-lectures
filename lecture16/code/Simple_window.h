
#pragma once 

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

struct Simple_window : Graph_lib::Window {
    Simple_window(Graph_lib::Point xy, int w, int h, const string& title );

    void wait_for_button(); // simple event loop

private:
    Graph_lib::Button next_button;     // the "next" button
    bool button_pushed;     // implementation detail

    static void cb_next(Graph_lib::Address, Graph_lib::Address); // callback for next_button
    void next();            // action to be done when next_button is pressed

};
