#include "points.h"

size_t get_points_size(const points_t &points)
{
    return points.len;
}


void set_points_count(points_t &points, const size_t count)
{
    points.len = count;
}


point_t *get_points_array(points_t &points)
{
    return points.data;
}

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

point_t get_point(const points_t &points, const int index)
{
    return points.data[index];
}

void points_init(points_t &points)
{
    points.data = NULL;
    points.len = 0;
}

int read_points(points_t &points, FILE *file, int &error_flag)
{
    char line[256];
    size_t point_count = 0;

    if (!fgets(line, sizeof(line), file) || sscanf(line, "v %zu", &point_count) != 1)
    {
        printf("Error: invalid vertex count format\n");
        error_flag = DATA_ERROR;
    }

    if (!error_flag && points_alloc_count(points, point_count) != EXIT_SUCCESS)
    {
        printf("Memory allocation error for points\n");
        error_flag = MEMORY_ERROR;
    }

    for (size_t i = 0; !error_flag && i < point_count; i++)
    {
        error_flag = read_point(file, points.data[i], error_flag);
        if (error_flag != EXIT_SUCCESS)
        {
            points_free(points);
        }
    }

    return error_flag;
}

void export_points(FILE *file, points_t &points)
{
    size_t p_count = get_points_size(points);
    point_t *points_arr = get_points_array(points);

    fprintf(file, "v %zu\n", p_count);
    for (size_t i = 0; i < p_count; i++)
    {
        export_point(file, points_arr[i]);
    }
}

int deepcopy_points(points_t &dst, const points_t &src)
{
    int error_flag = EXIT_SUCCESS;
    
    error_flag = points_alloc_count(dst, src.len);
    
    for (size_t i = 0; !error_flag && i < src.len; i++)
    {
        deepcopy_point(dst.data[i], src.data[i]);
    }
    
    return error_flag;
}