#include "point.h"
#include "figure.h"

int check_file_opened(FILE *file)
{
    int error_flag = EXIT_SUCCESS;
    if (!file)
    {
        error_flag = FILE_ERROR;
    }
    return error_flag;
}

void center_init(point_t &center)
{
    center = {0, 0, 0};
}

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

// int read_point_line(char *line, FILE *file)
// {
//     int error_flag = EXIT_SUCCESS;
//     error_flag = check_file_opened(file);
//     if (!error_flag)
//     {
//         if (!fgets(line, BUFSIZ, file))
//         {
//             printf("Error: not enough edge data\n");
//             error_flag = DATA_ERROR;
//         }
//     }
    
//     return error_flag;
// }

int get_point_data(double *x, double *y, double *z, FILE *file)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        if (fscanf(file, "%lf %lf %lf", x, y, z) != 3)
        {
            printf("Error: invalid vertex format\n");
            error_flag = DATA_ERROR;
        }
    }
    
    return error_flag;
}

int read_point(FILE *file, point_t &point)
{
    int error_flag = EXIT_SUCCESS;
    // char line[BUFSIZ];
    double x, y, z;
    error_flag = check_file_opened(file);

    if (!error_flag)
    {    
        error_flag = get_point_data(&x, &y, &z, file);  
        if (!error_flag)
            set_point(point, x, y, z);

    }
    
    
    return error_flag;
}

int export_point(FILE *file, const point_t &point)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
        fprintf(file, "%.6f %.6f %.6f\n", point.x, point.y, point.z);
    return error_flag;
}
 
void deepcopy_point(point_t &dst, const point_t &src)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}

void calc_center(point_t &center, point_t point)
{
    center.x += point.x;
    center.y += point.y;
    center.z += point.z;
}

void calc_avg_center(point_t &center, const size_t points_count)
{
    center.x /= points_count;
    center.y /= points_count;
    center.z /= points_count;
}

void deepcopy_point_wrapper(point_t *dst_data, const point_t *src_data, const size_t src_len)
{
    for (size_t i = 0; i < src_len; i++)
    {
        deepcopy_point(dst_data[i], src_data[i]);
    }
}

void translate_center(point_t &center, const move_data_t data)
{
    translate_point(center, data.dx, data.dy, data.dz);
}