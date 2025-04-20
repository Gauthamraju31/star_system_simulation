#ifndef _X11_H_
#define _X11_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// --- X11 Display Context ---
typedef struct {
    Display *display;
    int screen;
    Window window;
    GC gc;
    unsigned int width;
    unsigned int height;
} X11Disp;

// --- Function Declarations ---
bool init_x(X11Disp *x11, unsigned int width, unsigned int height);
void handle_x11_events(Display *display, Window window);
void close_x(X11Disp *x11);
void redraw_x(X11Disp *x11);

#endif