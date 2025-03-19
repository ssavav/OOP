#include "points.h"

int points_alloc_count(point_t *&points, size_t count)
{
    int error_flag = EXIT_SUCCESS;
    points = (point_t*)malloc(sizeof(point_t) * count);
    if (!points)
        error_flag = MEMORY_ERROR;
    
    return error_flag;
}

void points_free(point_t *data) // оставить только дату
{
    free(data);    

    // points.len = 0;
}

void points_free_wrapper(points_t &points)
{
    points_free(points.data);
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
    int error_flag = EXIT_SUCCESS;
    for (size_t i = 0; !error_flag && (i < len); i++)
    {
        scale_point(arr[i], data.sx, data.sy, data.sz);
    }
    return error_flag;
}

void translate_points(point_t *arr, const size_t len, const move_data_t data)
{
    for (size_t i = 0; i < len; i++)
    {
        translate_point(arr[i], data.dx, data.dy, data.dz);
    }
}

void translate_points_to_origin(points_t &points, const point_t &center)
{
    move_data_t to_origin = {-center.x, -center.y, -center.z};
    translate_points_origin(points, to_origin);
}

void translate_points_from_origin(points_t &points, const point_t &center)
{
    move_data_t from_origin = {center.x, center.y, center.z};
    translate_points_origin(points, from_origin);
}

void rotate_points_all(points_t &points, point_t &center, const rotate_data_t data)
{
    translate_points_to_origin(points, center);

    rotate_points_x(points.data, points.len, data.ax);
    rotate_points_y(points.data, points.len, data.ay);
    rotate_points_z(points.data, points.len, data.az);

    translate_points_from_origin(points, center);

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

int read_points_count(size_t &point_count, FILE *file)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        if (fscanf(file, "%zu", &point_count) != 1)
        {
            printf("Error: invalid vertex count format\n");
            error_flag = DATA_ERROR;
        }
    }
    return error_flag;
}

int read_points_wrapper(point_t *points, size_t point_count, FILE *file)
{
    
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        for (size_t i = 0; !error_flag && i < point_count; i++)
            error_flag = read_point(file, points[i]);
    }
    
    return error_flag;
}

// int read(FILE *file, points_t &points)
// {
//     int error_flag = EXIT_SUCCESS;
//     error_flag = check_file_opened(file);
//     if (!error_flag)
//     {
//         error_flag = read_points_wrapper(points.data, points.len, file);
//         if (error_flag)
//         {
//             points_clear(points);
//         }
//     }   

//     return error_flag;
// }

int read_points(points_t &points, FILE *file)
{
    int error_flag = EXIT_SUCCESS;

    //вынесено
        error_flag = read_points_count(points.len, file);
        if (!error_flag)
        {
            error_flag = points_alloc_count(points.data, points.len);
            if (!error_flag)
            {
                error_flag = read_points_wrapper(points.data, points.len, file);
                if (error_flag)
                {
                    points_free(points.data);
                }
            } 
        }
    
    return error_flag;
}

int export_point_wrapper(FILE *file, const point_t *data, const size_t len)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    
    if (!error_flag)
    {
        for (size_t i = 0; !error_flag && i < len; i++)
        {
            error_flag = export_point(file, data[i]);
        }
    }
    
    return error_flag;
}

int export_points(FILE *file, points_t &points)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        fprintf(file, "%zu\n", points.len);
        error_flag = export_point_wrapper(file, points.data, points.len);
    }
    
    return error_flag;
}

int deepcopy_points(points_t &dst, const points_t &src)
{
    int error_flag = EXIT_SUCCESS;
    
    error_flag = points_alloc_count(dst.data, src.len);
    if (!error_flag)
    {
        dst.len = src.len;
        deepcopy_point_wrapper(dst.data, src.data, src.len);
    }
    
    return error_flag;
}

void calc_center_wrapper(point_t &center, point_t *data, const size_t points_count)
{
    for (size_t i = 0; i < points_count; i++)
    {
        calc_center(center, data[i]);
    }
}

void calc_points_center(point_t &center, points_t points, const size_t points_count)
{
    calc_center_wrapper(center, points.data, points_count);
    calc_avg_center(center, points_count);
}

void translate_points_origin(points_t &points, const move_data_t data)
{
    translate_points(points.data, points.len, data);
}

void translate_points_all(points_t &points, point_t &center, const move_data_t data)
{
    translate_center(center, data);
    translate_points(points.data, points.len, data);
}

int scale_points_all(points_t &points, point_t &center, const scale_data_t data)
{
    
    int error_flag = check_scale_data(data);
    if (!error_flag)
    {    
        translate_points_to_origin(points, center);

        error_flag = scale_points(points.data, points.len, data);
        
        translate_points_from_origin(points, center);
    }
    
    return error_flag;
}