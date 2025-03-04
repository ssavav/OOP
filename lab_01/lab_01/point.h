#ifndef POINT_H
#define POINT_H

#include "consts.h"

struct point_t
{
    double x, y, z;
};

struct points_t
{
    point_t *data;
    size_t len;
};

void translate_points(const double dx, const double dy, const double dz, points_t &points);
void scale_points(const double sx, const double sy, const double sz, points_t &points);
void rotate_points(const double ax, const double ay, const double az, points_t &points);
#endif // POINT_H
