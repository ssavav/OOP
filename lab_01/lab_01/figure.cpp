#include "figure.h"
#include "helpful.h"

figure_t &figure_alloc()
{
    static figure_t figure;

    figure.points.data = nullptr;
    figure.points.len = 0;

    figure.edges.data = nullptr;
    figure.edges.len = 0;

    return figure;
}

void figure_free(figure_t &figure)
{
    points_free(figure.points);
    edges_free(figure.edges);
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
        if (!fgets(line, sizeof(line), file))
        {
            printf("Error: not enough vertex data\n");
            points_free(points);
            error_flag = DATA_ERROR;
        }

        double x, y, z;
        if (!error_flag && sscanf(line, "%lf %lf %lf", &x, &y, &z) != 3)
        {
            printf("Error: invalid vertex format\n");
            points_free(points);
            error_flag = DATA_ERROR;
        }

        set_point(points.data[i], x, y, z);
    }

    return error_flag;
}

int read_edges(edges_t &edges, FILE *file, int &error_flag)
{
    char line[256];
    size_t edge_count = 0;

    if (!fgets(line, sizeof(line), file) || sscanf(line, "e %zu", &edge_count) != 1)
    {
        printf("Error: invalid edge count format\n");
        error_flag = FILE_ERROR;
    }

    if (!error_flag && edges_alloc_count(edges, edge_count) != EXIT_SUCCESS)
    {
        error_flag = MEMORY_ERROR;
    }

    for (size_t i = 0; !error_flag && i < edge_count; i++)
    {
        if (!fgets(line, sizeof(line), file))
        {
            printf("Error: not enough edge data\n");
            edges_free(edges);
            error_flag = DATA_ERROR;
        }

        size_t start, end;
        if (!error_flag && sscanf(line, "%zu %zu", &start, &end) != 2)
        {
            printf("Error: invalid edge format\n");
            edges_free(edges);
            error_flag = DATA_ERROR;
        }

        set_edge(edges.data[i], start, end);
    }

    return error_flag;
}

int read_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error while opening the file: %s\n", filename);
        error_flag = FILE_ERROR;
    }

    read_points(figure.points, file, error_flag);
    if (error_flag == EXIT_SUCCESS)
    {
        read_edges(figure.edges, file, error_flag);
        if (error_flag != EXIT_SUCCESS)
        {
            points_free(figure.points);
        }
    }

    fclose(file);
    return error_flag;
}

int check_figure(figure_t &figure) // конст проблема
{
    int error_flag = EXIT_SUCCESS;

    size_t point_count = get_points_size(figure.points);
    size_t edge_count = get_edges_size(figure.edges);

    if (point_count == 0 || edge_count == 0)
        return DATA_ERROR;

    edge_t *edges = get_edges_array(figure.edges);
    for (size_t i = 0; i < edge_count; i++)
    {
        size_t start = get_edge_start(edges[i]);
        size_t end = get_edge_end(edges[i]);

        if (start < 1 || start > point_count || end < 1 || end > point_count)
        {
            printf("Error: edge %zu-%zu is invalid\n", start, end);
            return DATA_ERROR;
        }
    }

    return error_flag;
}


int export_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error, while opening the file %s for writing\n", filename);
        return FILE_ERROR;
    }

    point_t *points_arr = get_points_array(figure.points);
    edge_t *edges_arr = get_edges_array(figure.edges);
    size_t p_count = get_points_size(figure.points);
    size_t e_count = get_edges_size(figure.edges);

    fprintf(file, "v %zu\n", p_count);
    for (size_t i = 0; i < p_count; i++)
    {
        fprintf(file, "%.6f %.6f %.6f\n",
                points_arr[i].x,
                points_arr[i].y,
                points_arr[i].z);
    }

    fprintf(file, "e %zu\n", e_count);
    for (size_t i = 0; i < e_count; i++)
    {
        fprintf(file, "%zu %zu\n", edges_arr[i].start, edges_arr[i].end);
    }

    fclose(file);
    return error_flag;
}

void translate_figure(points_t &points, const move_data_t data)
{
    point_t *arr = get_points_array(points);
    size_t len = get_points_size(points);

    translate_points(arr, len, data);
}

int scale_figure(points_t &points, const scale_data_t data)
{
    point_t *arr = get_points_array(points);
    size_t len = get_points_size(points);

    int error = scale_points(arr, len, data);
    return error;
}

void rotate_figure(points_t &points, const rotate_data_t data)
{
    point_t *arr = get_points_array(points);
    size_t len = get_points_size(points);

    rotate_points_x(arr, len, data.ax);
    rotate_points_y(arr, len, data.ay);
    rotate_points_z(arr, len, data.az);
    // rotate_points_y(points, data.ay);
    // rotate_points_z(points, data.az);
}