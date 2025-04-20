#include "core.h"

// ---- Sphere Lifecycle ----

Sphere *sphere_create(PosVec position, float radius, Color color, float mass, MomVec momentum) {
  Sphere *s = (Sphere *)malloc(sizeof(Sphere));
  if (!s) {
    fprintf(stderr, "Error: Failed to allocate memory for sphere.\n");
    return NULL;
  }
  s->position = position;
  s->momentum = momentum;
  s->radius = radius;
  s->mass = mass;
  s->force = (Vector){0, 0, 0};
  s->color = color;
  s->make_trail = 0;
  s->trail_length = 0;
  s->trail = NULL;
  return s;
}

void sphere_free(Sphere *s) {
  if (s) {
    if (s->trail) free(s->trail);
    free(s);
  }
}