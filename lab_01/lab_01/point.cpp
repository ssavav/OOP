#include "point.h"

void translate_point(const double dx, const double dy, const double dz, point_t &point)
{
    point.x += dx;
    point.y += dy;
    point.z += dz;
}

void translate_points(const double dx, const double dy, const double dz, points_t &points)
{
    for (size_t i = 0; i < points.len; i++)
    {
        translate_point(dx, dy, dz, points.data[i]);
    }
}

void scale_point(const double sx, const double sy, const double sz, point_t &point)
{
    point.x *= sx;
    point.y *= sy;
    point.z *= sz;
}

void scale_points(const double sx, const double sy, const double sz, points_t &points)
{
    for (size_t i = 0; i < points.len; i++)
    {
        scale_point(sx, sy, sz, points.data[i]);
    }
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

void rotate_model_x(const double angle, points_t &points) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < points.len; i++) 
    {
        rotate_point_x(points.data[i], cos_a, sin_a);
    }
}

void rotate_model_y(const double angle, points_t &points) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < points.len; i++)
    {
        rotate_point_y(points.data[i], cos_a, sin_a);
    }
}

void rotate_model_z(const double angle, points_t &points) 
{
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (size_t i = 0; i < points.len; i++) 
    {
        rotate_point_z(points.data[i], cos_a, sin_a);
    }
}

void rotate_points(const double ax, const double ay, const double az, points_t &points)
{
    rotate_model_x(ax, points);
    rotate_model_y(ay, points);
    rotate_model_z(az, points);
}
