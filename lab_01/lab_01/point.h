#ifndef POINT_H
#define POINT_H

#include "consts.h"
#include "request_manager.h"

struct point_t
{
    double x, y, z;
};

// void translate_points(points_t &points, const move_data_t data);
// int scale_points(points_t &points, const scale_data_t data);
// void rotate_points(points_t &points, const rotate_data_t data);
// int points_alloc(points_t &points);
// void points_free(points_t &points);
void center_init(point_t &center);
void calc_center(point_t &center, point_t point);
void calc_avg_center(point_t &center, const size_t points_count);

void set_point(point_t &point, const double x, const double y, const double z);

void rotate_point_x(point_t &point, const double cos_a, const double sin_a);
void rotate_point_y(point_t &point, const double cos_a, const double sin_a);
void rotate_point_z(point_t &point, const double cos_a, const double sin_a);

int check_scale_data(const scale_data_t data);
void scale_point(point_t &point, const double sx, const double sy, const double sz);

void translate_point(point_t &point, const double dx, const double dy, const double dz);
void translate_center(point_t &center, const move_data_t data);

int read_point(FILE *file, point_t &point);
int export_point(FILE *file, const point_t &point);
void deepcopy_point(point_t &dst, const point_t &src);
void deepcopy_point_wrapper(point_t *dst_data, const point_t *src_data, const size_t src_len);
// int check_file_opened(FILE *file);
#endif // POINT_H
