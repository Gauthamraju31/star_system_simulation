#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "core.h"

// ---- Physics Functions ----

static inline Vector gforce(Sphere *a, Sphere *b) {
  Vector r_vec = vec_sub(a->position, b->position);
  float r_mag = vec_mag(r_vec);

  if (r_mag == 0) return (Vector){0, 0, 0};  // Prevent division by zero

  Vector r_hat = vec_normalize(r_vec);
  float force_mag = (GRAVITY_CONSTANT * a->mass * b->mass) / (r_mag * r_mag);
  return vec_scale(r_hat, -force_mag);
}

static inline void update_momentum(Sphere *body, float dt) {
  body->momentum = vec_add(body->momentum, vec_scale(body->force, dt));
}

static inline void update_position(Sphere *body, float dt) {
  Vector velocity = vec_scale(body->momentum, 1.0f / body->mass);
  body->position = vec_add(body->position, vec_scale(velocity, dt));
}

#endif