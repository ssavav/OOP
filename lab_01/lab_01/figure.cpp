#include "figure.h"

figure_t &figure_alloc()
{
    static figure_t figure;

    points_init(figure.points);
    edges_init(figure.edges);

    return figure;
}

void figure_free(figure_t &figure)
{
    points_free(figure.points);
    edges_free(figure.edges);
}

int deepcopy_figure(figure_t &dst, const figure_t &src)
{
    int error_flag = EXIT_SUCCESS;
    
    // figure_free(dst);
    
    error_flag = deepcopy_points(dst.points, src.points);
    if (!error_flag)
    {
        error_flag = deepcopy_edges(dst.edges, src.edges);
        if (error_flag)
            points_free(dst.points);
    }
    
    return error_flag;
}

int read_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    figure_t temp_figure = figure_alloc();

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error while opening the file: %s\n", filename);
        error_flag = FILE_ERROR;
    }

    if (!error_flag)
    {
        read_points(temp_figure.points, file, error_flag);
        if (!error_flag)
        {
            read_edges(temp_figure.edges, file, error_flag);
            // if (error_flag) points_free(temp_figure.points);
        }
    }

    error_flag = check_figure(temp_figure);
    printf("%d\n", error_flag);
    if (!error_flag)
    {
        deepcopy_figure(figure, temp_figure);
    }
    else
        figure_free(temp_figure);

    fclose(file);
    return error_flag;
}

int check_figure(figure_t &figure)
{
    int error_flag = EXIT_SUCCESS;

    size_t point_count = get_points_size(figure.points);
    
    if (point_count == 0)
        error_flag = DATA_ERROR;

    if (!error_flag)
        error_flag = check_edges(figure.edges, point_count);

    return error_flag;
}

int export_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error, while opening the file %s for writing\n", filename);
        error_flag = FILE_ERROR;
    }

    if (!error_flag)
    {
        export_points(file, figure.points);
        export_edges(file, figure.edges);
        fclose(file);
    }
    
    return error_flag;
}

void translate_figure(figure_t &figure, const move_data_t data)
{
    point_t *arr = get_points_array(figure.points);
    size_t len = get_points_size(figure.points);
    
    translate_points(arr, len, data);
}

int scale_figure(figure_t &figure, const scale_data_t data)
{
    point_t *arr = get_points_array(figure.points);
    size_t len = get_points_size(figure.points);

    int error = scale_points(arr, len, data);
    return error;
}

void rotate_figure(figure_t &figure, const rotate_data_t data)
{
    point_t *arr = get_points_array(figure.points);
    size_t len = get_points_size(figure.points);

    rotate_points_x(arr, len, data.ax);
    rotate_points_y(arr, len, data.ay);
    rotate_points_z(arr, len, data.az);
}