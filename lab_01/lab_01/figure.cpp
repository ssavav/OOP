#include "figure.h"

void set_points_count(points_t &points, size_t count) {
    points.len = count;
}

// Функция для установки количества рёбер
void set_edges_count(edges_t &edges, size_t count) {
    edges.len = count;
}

// Функция для получения массива точек
point_t *get_points_array(points_t &points) {
    return points.data;
}

// Функция для получения массива рёбер
edge_t *get_edges_array(edges_t &edges) {
    return edges.data;
}

// Функция для установки координат точки
void set_point(point_t &point, double x, double y, double z) {
    point.x = x;
    point.y = y;
    point.z = z;
}

// Функция для установки рёбер
void set_edge(edge_t &edge, size_t start, size_t end) {
    edge.start = start;
    edge.end = end;
}


int read_figure(const char *filename, figure_t &figure)
{
    int error_flag = EXIT_SUCCESS;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error, while opening the file %s\n", filename);
        error_flag = FILE_ERROR;
    }

    size_t point_count = 0;
    size_t edge_count = 0;
    int reading_points = 0;
    int reading_edges = 0;

    char line[256];
    while (file && !error_flag && fgets(line, sizeof(line), file))
    {
        char *p = strchr(line, '\n');
        if (p)
            *p = '\0';

        if (strcmp(line, "v") == 0)
        {
            reading_points = 1;
            reading_edges = 0;
            continue;
        }
        else if (strcmp(line, "e") == 0)
        {
            reading_points = 0;
            reading_edges = 1;
            continue;
        }

        if (reading_points)
        {
            double x, y, z;
            if (sscanf(line, "%lf %lf %lf", &x, &y, &z) == 3)
            {
                figure.points.data[point_count].x = x;
                figure.points.data[point_count].y = y;
                figure.points.data[point_count].z = z;
                point_count++;
            }
        }
        else if (reading_edges)
        {
            size_t start, end;
            if (sscanf(line, "%zu %zu", &start, &end) == 2)
            {
                figure.edges.data[edge_count].start = start;
                figure.edges.data[edge_count].end = end;
                edge_count++;
            }
        }
    }

    figure.points.len = point_count;
    figure.edges.len = edge_count;
    if (error_flag != FILE_ERROR)
        fclose(file);

    return error_flag;
}

int check_figure(figure_t &figure)
{
    int error_flag = EXIT_SUCCESS;
    if (figure.edges.len <= 0 || figure.points.len <= 0)
        error_flag = DATA_ERROR;
    
    return error_flag;
}

int export_figure(const char *filename, figure_t &figure)
{
    int error_flag = EXIT_SUCCESS;
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error, while opening the file %s for writing\n", filename);
        error_flag = FILE_ERROR;
    }

    if (error_flag != FILE_ERROR)
    {
        fprintf(file, "v\n");
        for (size_t i = 0; i < figure.points.len; i++)
        {
            fprintf(file, "%.6f %.6f %.6f\n",
                    figure.points.data[i].x,
                    figure.points.data[i].y,
                    figure.points.data[i].z);
        }

        fprintf(file, "e\n");
        for (size_t i = 0; i < figure.edges.len; i++)
        {
            fprintf(file, "%zu %zu\n", figure.edges.data[i].start, figure.edges.data[i].end);
        }

        fclose(file);
    }

    return error_flag;
}
