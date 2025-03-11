#include "point.h"
#include "figure.h"

int points_alloc(points_t &points)
{
    int error = EXIT_SUCCESS;
    points.data = (point_t*)malloc(sizeof(point_t) * MAX_VERTICES);
    if (!points.data)
    {
        error = MEMORY_ERROR;
    }
    return error;
}

void points_free(points_t &points)
{
    free(points.data);
}

void translate_point(point_t &point, const double dx, const double dy, const double dz)
{
    point.x += dx;
    point.y += dy;
    point.z += dz;
}

void translate_points(points_t &points, const move_data_t data)
{
    for (size_t i = 0; i < points.len; i++)
    {
        translate_point(points.data[i], data.dx, data.dy, data.dz);
    }
}

int check_scale_data(const scale_data_t data)
{
    if (data.sx <= 0 || data.sy <= 0 || data.sz <= 0)
    {
        return DATA_ERROR;
    }
    return EXIT_SUCCESS;
    
}

void scale_point(point_t &point, const double sx, const double sy, const double sz)
{
    point.x *= sx;
    point.y *= sy;
    point.z *= sz;
}

int scale_points(points_t &points, const scale_data_t data)
{
    int error = check_scale_data(data);
    for (size_t i = 0; !error && (i < points.len); i++)
    {
        scale_point(points.data[i], data.sx, data.sy, data.sz);
    }
    return error;
}

double to_rad(const double angle)
{
    return (angle * PI / 180.0);
}

void rotate_point_x(point_t &point, const double cos_a, const double sin_a)
{
    double y_new = point.y * cos_a - point.z * sin_a;
    double z_new = point.y * sin_a + point.z * cos_a;

    point.y = y_new;
    point.z = z_new;
}

void rotate_point_y(point_t &point, const double cos_a, const double sin_a)
{
    double x_new = point.x * cos_a + point.z * sin_a;
    double z_new = -point.x * sin_a + point.z * cos_a;

    point.x = x_new;
    point.z = z_new;
}

void rotate_point_z(point_t &point, const double cos_a, const double sin_a)
{
    double x_new = point.x * cos_a - point.y * sin_a;
    double y_new = point.x * sin_a + point.y * cos_a;

    point.x = x_new;
    point.y = y_new;
}

void rotate_x(points_t &points, const double angle) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < points.len; i++) 
    {
        rotate_point_x(points.data[i], cos_a, sin_a);
    }
}

void rotate_y(points_t &points, const double angle) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < points.len; i++)
    {
        rotate_point_y(points.data[i], cos_a, sin_a);
    }
}

void rotate_z(points_t &points, const double angle) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < points.len; i++) 
    {
        rotate_point_z(points.data[i], cos_a, sin_a);
    }
}

void rotate_points(points_t &points, const rotate_data_t data)
{
    rotate_x(points, data.ax);
    rotate_y(points, data.ay);
    rotate_z(points, data.az);
}
