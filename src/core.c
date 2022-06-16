#include "core.h"

#define GRAVITY_CONSTANT 1

Vector gforce(Sphere *p1, Sphere *p2)
{
  //float r_vec = p1->pos - p2->pos;
  Vector r_vec, r_hat, force_vec;
  float r_mag, force_mag;

  r_vec.x = p1->position.x - p2->position.x;
  r_vec.y = p1->position.y - p2->position.y;
  r_vec.z = p1->position.z - p2->position.z;
  r_mag = sqrt(r_vec.x * r_vec.x + r_vec.y * r_vec.y + r_vec.z * r_vec.z);
  r_hat.x = r_vec.x / r_mag;
  r_hat.y = r_vec.y / r_mag;
  r_hat.z = r_vec.z / r_mag;

  force_mag = (GRAVITY_CONSTANT * p1->mass * p2->mass) / (r_mag * r_mag);
  force_vec.x = -force_mag * r_hat.x;
  force_vec.y = -force_mag * r_hat.y;
  force_vec.z = -force_mag * r_hat.z;
  return force_vec;
}

Sphere *sphere_create(PosVec position, float radius, Color color, float mass, MomVec momentum)
{
  Sphere *sphere = (Sphere *)malloc(sizeof(Sphere));
  sphere->position = position;
  sphere->momentum = momentum;
  sphere->radius = radius;
  sphere->mass = mass;
  sphere->force.x = 0;
  sphere->force.y = 0;
  sphere->force.z = 0;
  sphere->color = color;
  return sphere;
}

void sphere_free(Sphere *sphere)
{
  free(sphere);
}

void update_momentum(Sphere *body, float dt)
{
  body->momentum.x += body->force.x * dt;
  body->momentum.y += body->force.y * dt;
  body->momentum.z += body->force.z * dt;
}

void update_position(Sphere *body, float dt)
{
  body->position.x += (body->momentum.x / body->mass) * dt;
  body->position.y += (body->momentum.y / body->mass) * dt;
  body->position.z += (body->momentum.z / body->mass) * dt;
}

int test()
{
  Sphere *star, *planet;

  // Star parameters
  Vector pos = {0, 0, 0};
  Color color = {255, 255, 0};
  Vector mom = {0, 0, 0};

  star = sphere_create(pos, 0.2, color, 1000, mom);

  // Planet parameters
  pos.x = 1;
  mom.y = 30;
  planet = sphere_create(pos, 0.2, color, 1, mom);

  float dt = 0.0001;
  float t = 0;
  int steps = 500;
  while (steps)
  {

    //Calculate force
    star->force = gforce(star, planet);
    planet->force = gforce(planet, star);

    //Update momentum
    update_momentum(star, dt);
    update_momentum(planet, dt);

    //Update position
    update_position(star, dt);
    update_position(planet, dt);

    t += dt;
    steps--;

    printf("\nPosition of Star %0.3f:%0.3f:%0.3f, Poisiton of Planet %0.3f:%0.3f:%0.3f", star->position.x, star->position.y, star->position.z,
           planet->position.x, planet->position.y, planet->position.z);
  }

  free(star);
  free(planet);
  return 0;
}
