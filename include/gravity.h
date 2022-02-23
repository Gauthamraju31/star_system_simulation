#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _Vector
{
  float x;
  float y;
  float z;
}Vector;

typedef Vector PosVec;
typedef Vector MomVec;
typedef Vector ForceVec;

typedef struct _Color
{
  unsigned int r;
  unsigned int g;
  unsigned int b;
  unsigned int a;
}Color;

typedef struct _Sphere{
  PosVec position;
  MomVec momentum;	   
  float radius;
  float mass;
  ForceVec force;
  Color color;
  unsigned int make_trail;
  unsigned int trail_length;
  Vector *trail;
}Sphere;

Sphere* sphere_create(PosVec position, float radius, Color color, float mass, MomVec momentum, unsigned int make_trail, unsigned int trail_length);

void sphere_free(Sphere *sphere);

Vector gforce(Sphere* body1, Sphere* body2);

void update_momentum(Sphere *body, float dt);

void update_position(Sphere *body, float dt);

void update_trail(Sphere *sphere);