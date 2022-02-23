#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/Xos.h>
#include <stdlib.h>


typedef struct _X11Disp
{
  Display *dis;
  int screen;
  Window win;
  GC gc;
}X11Disp;


void init_x(X11Disp* x11_display, unsigned int width, unsigned int height);

void close_x(X11Disp* x11_display);

void redraw_x(X11Disp* x11_display);

