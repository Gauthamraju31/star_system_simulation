#ifndef _VEC_H_
#define _VEC_H_

#include <math.h>

typedef struct {
  float x, y, z;
} Vector;

typedef Vector PosVec;
typedef Vector MomVec;
typedef Vector ForceVec;

// ---- Vector Helpers ----

static inline Vector vec_sub(Vector a, Vector b) {
  return (Vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline Vector vec_add(Vector a, Vector b) {
  return (Vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline Vector vec_scale(Vector v, float s) {
  return (Vector){v.x * s, v.y * s, v.z * s};
}

static inline float vec_mag(Vector v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline Vector vec_normalize(Vector v) {
  float mag = vec_mag(v);
  if (mag == 0) return (Vector){0, 0, 0};
  return vec_scale(v, 1.0f / mag);
}

#endif