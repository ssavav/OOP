#include "figure.h"
#include "helpful.h"

figure_t &figure_alloc()
{

    static figure_t figure;

    points_alloc(figure.points);

    edges_alloc(figure.edges);

    return figure;
}

void figure_free(figure_t &figure)
{
    points_free(figure.points);
    edges_free(figure.edges);
}

void set_point(point_t &point, const double x, const double y, const double z)
{
    point.x = x;
    point.y = y;
    point.z = z;
}

void set_edge(edge_t &edge, const size_t start, const size_t end)
{
    edge.start = start;
    edge.end = end;
}

int read_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error, while opening the file %s\n", filename);
        return FILE_ERROR;
    }

    point_t *points_arr = get_points_array(figure.points);
    edge_t  *edges_arr  = get_edges_array(figure.edges);

    size_t point_count = 0;
    size_t edge_count  = 0;
    bool reading_points = false;
    bool reading_edges  = false;

    char line[256];
    while (!error_flag && fgets(line, sizeof(line), file))
    {
        char *p = strchr(line, '\n');
        if (p)
            *p = '\0';

        if (strcmp(line, "v") == 0)
        {
            reading_points = true;
            reading_edges  = false;
            continue;
        }
        else if (strcmp(line, "e") == 0)
        {
            reading_points = false;
            reading_edges  = true;
            continue;
        }

        if (reading_points)
        {
            double x, y, z;
            if (sscanf(line, "%lf %lf %lf", &x, &y, &z) == 3)
            {
                set_point(points_arr[point_count], x, y, z);
                point_count++;
            }
        }
        else if (reading_edges)
        {
            size_t start, end;
            if (sscanf(line, "%zu %zu", &start, &end) == 2)
            {
                set_edge(edges_arr[edge_count], start, end);
                edge_count++;
            }
        }
    }

    fclose(file);

    set_points_count(figure.points, point_count);
    set_edges_count(figure.edges, edge_count);

    printf("v:%zu e:%zu\n", get_points_size(figure.points), get_edges_size(figure.edges));
    return error_flag;
}

int check_figure(const figure_t &figure)
{
    int error_flag = EXIT_SUCCESS;
    if (get_points_size(figure.points) == 0 || get_edges_size(figure.edges) == 0)
        error_flag = DATA_ERROR;
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

    fprintf(file, "v\n");
    for (size_t i = 0; i < p_count; i++)
    {
        fprintf(file, "%.6f %.6f %.6f\n",
                points_arr[i].x,
                points_arr[i].y,
                points_arr[i].z);
    }

    fprintf(file, "e\n");
    for (size_t i = 0; i < e_count; i++)
    {
        fprintf(file, "%zu %zu\n", edges_arr[i].start, edges_arr[i].end);
    }

    fclose(file);
    return error_flag;
}
