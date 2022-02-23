#include "x11.h"

void init_x(X11Disp* x11_display, unsigned int width, unsigned int height)
{
  unsigned long black, white;
  x11_display->dis = XOpenDisplay((char *)0);
  x11_display->screen = DefaultScreen(x11_display->dis);
  black = BlackPixel(x11_display->dis, x11_display->screen);
  white = WhitePixel(x11_display->dis, x11_display->screen);
  x11_display->win = XCreateSimpleWindow(x11_display->dis, DefaultRootWindow(x11_display->dis),0,0,
                  width,height,5,white,black);
  XSetStandardProperties(x11_display->dis, x11_display->win, "Star System","Star!",None,NULL,0,NULL);
  XSelectInput(x11_display->dis, x11_display->win, ExposureMask|ButtonPressMask|KeyPressMask);
  x11_display->gc=XCreateGC(x11_display->dis, x11_display->win, 0,0);
  XSetBackground(x11_display->dis, x11_display->gc, white);
  XSetForeground(x11_display->dis, x11_display->gc, black);
  XClearWindow(x11_display->dis, x11_display->win);
  XMapRaised(x11_display->dis, x11_display->win);
};


void close_x(X11Disp* x11_display)
{
  XFreeGC(x11_display->dis,x11_display->gc);
  XDestroyWindow(x11_display->dis,x11_display->win);
  XCloseDisplay(x11_display->dis);
  exit(1);
}

void redraw_x(X11Disp* x11_display)
{
  XClearWindow(x11_display->dis, x11_display->win);
}
