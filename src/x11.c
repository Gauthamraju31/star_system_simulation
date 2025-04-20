#include "x11.h"


extern bool running;

bool init_x(X11Disp *x11, unsigned int width, unsigned int height) {
    if (!x11) return false;

    x11->width = width;
    x11->height = height;

    x11->display = XOpenDisplay(NULL);
    if (!x11->display) {
        fprintf(stderr, "Error: Cannot open X display.\n");
        return false;
    }

    x11->screen = DefaultScreen(x11->display);
    unsigned long black = BlackPixel(x11->display, x11->screen);
    unsigned long white = WhitePixel(x11->display, x11->screen);

    x11->window = XCreateSimpleWindow(
        x11->display,
        DefaultRootWindow(x11->display),
        0, 0,
        width, height,
        5,
        white,
        black
    );

    XSetStandardProperties(
        x11->display, x11->window,
        "Star System", "Star!",
        None, NULL, 0, NULL
    );

    XSelectInput(
        x11->display, x11->window,
        ExposureMask | ButtonPressMask | KeyPressMask
    );

    x11->gc = XCreateGC(x11->display, x11->window, 0, 0);
    XSetBackground(x11->display, x11->gc, white);
    XSetForeground(x11->display, x11->gc, black);

    XClearWindow(x11->display, x11->window);
    XMapRaised(x11->display, x11->window);

    return true;
}

void handle_x11_events(Display *display, Window window) {
    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);

        if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);

            if (key == XK_q) {
                running = false;
                return;
            }
        }

        if (event.type == ClientMessage) {
            running = false;
            return;
        }
    }
}


void close_x(X11Disp *x11) {
    if (!x11 || !x11->display) return;

    XFreeGC(x11->display, x11->gc);
    XDestroyWindow(x11->display, x11->window);
    XCloseDisplay(x11->display);

    x11->display = NULL;
}

void redraw_x(X11Disp *x11) {
    if (!x11 || !x11->display) return;
    XClearWindow(x11->display, x11->window);
}
