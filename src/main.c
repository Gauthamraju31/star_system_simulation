#include <unistd.h>
#include "x11.h"
#include "core.h"

#define WIDTH 720
#define HEIGHT 720

unsigned long convert2Hex(unsigned int r, unsigned int g, unsigned int b)
{
       return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void draw_body(Sphere *body, X11Disp *solar_display)
{
       int body_offset_x = (int)(body->position.x * WIDTH) / 3 + WIDTH / 2;
       int body_offset_y = (int)(body->position.y * HEIGHT) / 3 + HEIGHT / 2;
       // int offset_z = (int) star->position.z*WIDTH;
       int body_offset_r = (int)(body->radius * HEIGHT / 3);
       unsigned long body_color = convert2Hex(body->color.r, body->color.g, body->color.b);

       XSetForeground(solar_display->dis, solar_display->gc, body_color);

       XFillArc(solar_display->dis, solar_display->win, solar_display->gc,
                body_offset_x - body_offset_r, body_offset_y - body_offset_r,
                body_offset_r * 2, body_offset_r * 2, 0, 360 * 64);
       
}

int main()
{
       Sphere *star, *planet;

       // Star parameters
       Vector pos = {0, 0, 0};
       Color color = {255, 255, 0, 255};
       Vector mom = {0, 0, 0};

       star = sphere_create(pos, 0.2, color, 1000, mom);

       // Planet 1 parameters
       pos.x = 1;
       mom.y = 30;
       color.r = 0;
       planet = sphere_create(pos, 0.05, color, 1, mom);

       // Step initialization
       const float dt = 0.0001;
       float t = 0;
       int steps = 100000;

       // Window Initialization
       // XEvent event;
       // KeySym key;
       // char text[255];

       X11Disp solar_display;
       init_x(&solar_display, WIDTH, HEIGHT);

       // while (XPending(solar_display.dis))
       while (steps)
       {
              // XNextEvent(solar_display.dis, &event);
              // switch (event.type)
              // {
              // case KeyPress:
              //        XLookupString(&event.xkey, text, 255, &key, 0) == 1;
              //        if (text[0] == 'q')
              //        {
              //               goto end;
              //        }
              //        break;
              // default:
              //        break;
              // }

              //Calculate force for star
              star->force = gforce(star, planet);

              //Calculate force for planet
              planet->force = gforce(planet, star);

              //Update momentum
              update_momentum(star, dt);
              update_momentum(planet, dt);

              //Update position
              update_position(star, dt);
              update_position(planet, dt);

              t += dt;
              steps--;

              //      if (event.type==Expose && event.xexpose.count==0)
              //      {
              //             redraw_x(&solar_display);
              //      }

              // if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1)
              // {
              //        if (text[0] == 'q')
              //               close_x(&solar_display);
              // }

              // Draw the star and planets
              redraw_x(&solar_display);
              draw_body(star, &solar_display);
              draw_body(planet, &solar_display);

              // printf("\nPosition of Star %0.3f:%0.3f:%0.3f, Poisiton of Planet %0.3f:%0.3f:%0.3f\n", star->position.x, star->position.y, star->position.z,
              //        planet->position.x, planet->position.y, planet->position.z);

              XFlush(solar_display.dis);
              usleep(1000);
       }

// end:
       free(star);
       free(planet);
       close_x(&solar_display);
       return 0;
}
