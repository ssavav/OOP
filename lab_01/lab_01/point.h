#ifndef POINT_H
#define POINT_H

#include "consts.h"
#include "request_manager.h"

struct point_t
{
    double x, y, z;
};

struct points_t
{
    point_t *data;
    size_t len;
};

void translate_points(points_t &points, const move_data_t data);
int scale_points(points_t &points, const scale_data_t data);
void rotate_points(points_t &points, const rotate_data_t data);
int points_alloc(points_t &points);
void points_free(points_t &points);
#endif // POINT_H
