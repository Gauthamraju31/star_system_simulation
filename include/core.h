#ifndef _CORE_H_
#define _CORE_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"

// #define GRAVITY_CONSTANT 1e-3f

#define GRAVITY_CONSTANT 1

typedef struct {
  unsigned int r, g, b, a;
} Color;

typedef struct {
  PosVec position;
  MomVec momentum;
  float radius;
  float mass;
  ForceVec force;
  Color color;
  unsigned int make_trail;
  unsigned int trail_length;
  Vector *trail;
} Sphere;


Sphere* sphere_create(PosVec position, float radius, Color color, float mass, MomVec momentum);

void sphere_free(Sphere *sphere);

#endif