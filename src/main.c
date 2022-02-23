#include <unistd.h>
#include "x11.h"
#include "gravity.h"

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

       if (body->make_trail)
       {
              XArc trail_arcs[body->trail_length + 1];
              trail_arcs[body->trail_length + 1].x = body_offset_x;
              trail_arcs[body->trail_length + 1].y = body_offset_y;
              trail_arcs[body->trail_length + 1].width = body_offset_r;
              trail_arcs[body->trail_length + 1].height = body_offset_r;
              trail_arcs[body->trail_length + 1].angle1 = 0;
              trail_arcs[body->trail_length + 1].angle2 = 360 * 64;
              for (int i = 0; i < body->trail_length - 1; i++)
              {
                     int trail_offset_x = (int)(body->trail[i].x * WIDTH) / 3 + WIDTH / 2;
                     int trail_offset_y = (int)(body->trail[i].y * HEIGHT) / 3 + HEIGHT / 2;
                     int trail_offset_r = (int)(body->radius * HEIGHT / 25);

                     trail_arcs[i].x = trail_offset_x - trail_offset_r;
                     trail_arcs[i].y = trail_offset_y - trail_offset_r;
                     trail_arcs[i].width = trail_offset_r * 2;
                     trail_arcs[i].height = trail_offset_r * 2;
                     trail_arcs[i].angle1 = 0;
                     trail_arcs[i].angle2 = 360 * 64;
              }

              XFillArcs(solar_display->dis, solar_display->win, solar_display->gc, trail_arcs, body->trail_length);
       }
       else
       {
              XFillArc(solar_display->dis, solar_display->win, solar_display->gc,
                       body_offset_x - body_offset_r, body_offset_y - body_offset_r,
                       body_offset_r * 2, body_offset_r * 2, 0, 360 * 64);
       }
}

int main()
{
       Sphere *star, *planet1, *planet2;

       // Star parameters
       Vector pos = {0, 0, 0};
       Color color = {255, 255, 0, 255};
       Vector mom = {0, 0, 0};

       star = sphere_create(pos, 0.2, color, 1000, mom, 0, 5);

       // Planet 1 parameters
       pos.x = 1;
       mom.y = 30;
       color.r = 0;
       planet1 = sphere_create(pos, 0.05, color, 1, mom, 0, 5);

       // Planet 2 parameters
       pos.x = 0;
       pos.y = 0.5;
       mom.y = 0;
       mom.x = 20;
       color.g = 0;
       color.b = 255;
       planet2 = sphere_create(pos, 0.075, color, 1, mom, 0, 5);

       // Step initialization
       const float dt = 0.0001;
       float t = 0;
       int steps = 10000;

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
              Vector tmp_force = {0, 0, 0};
              tmp_force = gforce(star, planet1);
              star->force = gforce(star, planet2);
              star->force.x += tmp_force.x;
              star->force.y += tmp_force.y;
              star->force.z += tmp_force.z;

              //Calculate force for planet1
              tmp_force = gforce(planet1, star);
              planet1->force = gforce(planet1, planet2);
              planet1->force.x += tmp_force.x;
              planet1->force.y += tmp_force.y;
              planet1->force.z += tmp_force.z;

              //Calculate force for planet2
              tmp_force = gforce(planet2, star);
              planet2->force = gforce(planet2, planet1);
              planet2->force.x += tmp_force.x;
              planet2->force.y += tmp_force.y;
              planet2->force.z += tmp_force.z;

              // star->force = gforce(star, planet1) + gforce(star, planet2);
              // planet1->force = gforce(planet1, star) + gforce(planet1, planet2);
              // planet2->force = gforce(planet2, star) + gforce(planet2, planet1);

              //Update momentum
              update_momentum(star, dt);
              update_momentum(planet1, dt);
              update_momentum(planet2, dt);

              //Update position
              update_position(star, dt);
              update_position(planet1, dt);
              update_momentum(planet2, dt);

              //Update trail
              update_trail(star);
              update_trail(planet1);
              update_trail(planet2);

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
              {
                     redraw_x(&solar_display);
                     draw_body(star, &solar_display);
                     draw_body(planet1, &solar_display);
                     draw_body(planet2, &solar_display);
              }

              // printf("\nPosition of Star %0.3f:%0.3f:%0.3f, Poisiton of Planet %0.3f:%0.3f:%0.3f\n", star->position.x, star->position.y, star->position.z,
              //        planet->position.x, planet->position.y, planet->position.z);

              XFlush(solar_display.dis);
              usleep(1000);
       }

// end:
       free(star);
       free(planet1);
       free(planet2);
       close_x(&solar_display);
       return 0;
}
