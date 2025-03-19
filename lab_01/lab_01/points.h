#ifndef POINTS_H
#define POINTS_H

#include "point.h"

struct points_t
{
    point_t *data;
    size_t len;
};
size_t get_points_size(const points_t &points);
void set_points_count(points_t &points, const size_t count);
point_t* get_points_array(points_t &points);
point_t get_point(const points_t &points, const int index);

void translate_points(point_t *arr, const size_t len, const move_data_t data);
int scale_points(point_t *arr, const size_t len, const scale_data_t data);
void rotate_figure(points_t &points, const rotate_data_t data);
int points_alloc_count(point_t *&points, size_t count);
// обозвать клиром
void points_free(point_t *data);
void points_free_wrapper(points_t &points);

void rotate_points_x(point_t *arr, const size_t len, const double angle);
void rotate_points_y(point_t *arr, const size_t len, const double angle);
void rotate_points_z(point_t *arr, const size_t len, const double angle);
void rotate_points_all(points_t &points, point_t &center, const rotate_data_t data);

int read_points(points_t &points, FILE *file);
int export_points(FILE *file, points_t &points);
int deepcopy_points(points_t &dst, const points_t &src);
void points_init(points_t &points);

void calc_points_center(point_t &center, points_t points, size_t points_count);
void translate_points_origin(points_t &points, const move_data_t data);
void translate_points_all(points_t &points, point_t &center, const move_data_t data);
int scale_points_all(points_t &points, point_t &center, const scale_data_t data);

void translate_points_to_origin(points_t &points, const point_t &center);
void translate_points_from_origin(points_t &points, const point_t &center);

#endif // POINTS_H
