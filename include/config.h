#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdbool.h>
#include "core.h"
#include "vector.h"

#define FRAME_TIME_MS 16 // ~60 FPS
#define WIDTH 720
#define HEIGHT 720
#define MAX_BODIES 10

typedef struct {
    unsigned int timestep;
    unsigned int resolution;
    float gravity;
    int planet_count;
    unsigned int log_Level;
    struct {
        float mass;
        Vector position;
        Vector momentum;
        float radius;
        Color color;
    } bodies[MAX_BODIES];
} Config;

bool load_config(const char *filename, Config *cfg);

#endif
