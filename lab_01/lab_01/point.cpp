#include "point.h"
#include "figure.h"

void set_point(point_t &point, const double x, const double y, const double z)
{
    point.x = x;
    point.y = y;
    point.z = z;
}

void translate_point(point_t &point, const double dx, const double dy, const double dz)
{
    point.x += dx;
    point.y += dy;
    point.z += dz;
}

int check_scale_data(const scale_data_t data)
{
    int error_flag = EXIT_SUCCESS;
    if (data.sx <= 0 || data.sy <= 0 || data.sz <= 0)
        error_flag = DATA_ERROR;
        
    return error_flag;
    
}

void scale_point(point_t &point, const double sx, const double sy, const double sz)
{
    point.x *= sx;
    point.y *= sy;
    point.z *= sz;
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

int read_point(FILE *file, point_t &point, int &error_flag)
{
    char line[256];
    double x, y, z;

    if (!fgets(line, sizeof(line), file))
    {
        printf("Error: not enough vertex data\n");
        error_flag = DATA_ERROR;
    }

    if (sscanf(line, "%lf %lf %lf", &x, &y, &z) != 3)
    {
        printf("Error: invalid vertex format\n");
        error_flag = DATA_ERROR;
    }
    if (!error_flag)
        set_point(point, x, y, z);
    
    return error_flag;
}

void export_point(FILE *file, const point_t &point)
{
    fprintf(file, "%.6f %.6f %.6f\n", point.x, point.y, point.z);
}
 
void deepcopy_point(point_t &dst, const point_t &src)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}