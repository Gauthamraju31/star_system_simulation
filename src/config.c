#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Vector parse_vector(const char *value) {
    Vector v = {0, 0, 0};
    sscanf(value, "%f,%f,%f", &v.x, &v.y, &v.z);
    return v;
}

static Color parse_color(const char *value) {
    Color c = {0, 0, 0, 0};
    sscanf(value, "%d,%d,%d,%d", &c.r, &c.g, &c.b, &c.a);
    return c;
}

bool load_config(const char *filename, Config *cfg) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return false;

    char line[256];
    // int current_planet = -1;

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#' || strlen(line) < 3) continue;

        char key[64], value[128];
        if (sscanf(line, "%[^=]=%[^\n]", key, value) != 2) continue;

        // Trim
        char *k = strtok(key, " \t\r\n");
        char *v = strtok(value, " \t\r\n");

        if (strcmp(k, "loglevel")==0){
            cfg->log_Level = atoi(v);
        } else if (strcmp(k, "resolution")==0) {
            cfg->resolution = atoi(v);
        } else if (strcmp(k, "timestep")==0) {
            cfg->timestep = atoi(v);
        } else if (strcmp(k, "gravity") == 0) {
            cfg->gravity = atof(v);
        } else if (strncmp(k, "planet", 6) == 0) {
            int id = k[6] - '0';
            if (id >= MAX_BODIES) continue;
            if (id + 1 > cfg->planet_count) cfg->planet_count = id + 1;

            char *field = strchr(k, '.');
            if (!field) continue;
            field++; // Skip dot

            if (strcmp(field, "mass") == 0) {
                cfg->bodies[id].mass = atof(v);
            } else if (strcmp(field, "pos") == 0) {
                cfg->bodies[id].position = parse_vector(v);
            } else if (strcmp(field, "mom") == 0) {
                cfg->bodies[id].momentum = parse_vector(v);
            } else if (strcmp(field, "color") == 0) {
                cfg->bodies[id].color = parse_color(v);
            } else if (strcmp(field, "rad") == 0) {
                cfg->bodies[id].radius = atof(v);
            }
        }
    }

    fclose(fp);
    return true;
}
