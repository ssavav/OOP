#ifndef POINTS_H
#define POINTS_H

#include "point.h"

struct points_t
{
    point_t *data;
    size_t len;
};

void translate_points(point_t *arr, const size_t len, const move_data_t data);
int scale_points(point_t *arr, const size_t len, const scale_data_t data);
void rotate_figure(points_t &points, const rotate_data_t data);
int points_alloc_count(points_t &points, size_t count);
void points_free(points_t &points);

void rotate_points_x(point_t *arr, const size_t len, const double angle);
void rotate_points_y(point_t *arr, const size_t len, const double angle);
void rotate_points_z(point_t *arr, const size_t len, const double angle);

#endif // POINTS_H
