#include "points.h"

int points_alloc_count(points_t &points, size_t count)
{
    int error_flag = EXIT_SUCCESS;
    points.data = (point_t*)malloc(sizeof(point_t) * count);
    if (!points.data)
        error_flag = MEMORY_ERROR;

    points.len = count;
    return error_flag;
}

void points_free(points_t &points)
{
    free(points.data);
    points.len = 0;
}

double to_rad(const double angle)
{
    return (angle * PI / 180.0);
}

void rotate_points_x(point_t *arr, const size_t len, const double angle) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < len; i++) 
    {
        rotate_point_x(arr[i], cos_a, sin_a);
    }
}

void rotate_points_y(point_t *arr, const size_t len, const double angle) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < len; i++)
    {
        rotate_point_y(arr[i], cos_a, sin_a);
    }
}

void rotate_points_z(point_t *arr, const size_t len, const double angle) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < len; i++) 
    {
        rotate_point_z(arr[i], cos_a, sin_a);
    }
}
// points_t &points, const scale_data_t data
int scale_points(point_t *arr, const size_t len, const scale_data_t data)
{
    int error = check_scale_data(data);
    for (size_t i = 0; !error && (i < len); i++)
    {
        scale_point(arr[i], data.sx, data.sy, data.sz);
    }
    return error;
}


void translate_points(point_t *arr, const size_t len, const move_data_t data)
{
    for (size_t i = 0; i < len; i++)
    {
        translate_point(arr[i], data.dx, data.dy, data.dz);
    }
}