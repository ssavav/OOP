#include "edge.h"

void set_edge(edge_t &edge, const size_t start, const size_t end)
{
    edge.start = start;
    edge.end = end;
}

int get_edge_start(const edge_t edge)
{
    return edge.start;
}

int get_edge_end(const edge_t edge)
{
    return edge.end;
}

int read_edge(FILE *file, edge_t &edge, int &error_flag)
{
    char line[256];
    size_t start, end;

    if (!fgets(line, sizeof(line), file))
    {
        printf("Error: not enough edge data\n");
        error_flag = DATA_ERROR;
        return error_flag;
    }

    if (sscanf(line, "%zu %zu", &start, &end) != 2)
    {
        printf("Error: invalid edge format\n");
        error_flag = DATA_ERROR;
        return error_flag;
    }

    set_edge(edge, start, end);
    return EXIT_SUCCESS;
}


int export_edge(FILE *file, const edge_t &edge)
{
    fprintf(file, "%zu %zu\n", edge.start, edge.end);
    return EXIT_SUCCESS;
}

void deepcopy_edge(edge_t &dst, const edge_t &src)
{
    dst.start = src.start;
    dst.end = src.end;
}

int check_edge(const edge_t &edge, const size_t point_count)
{
    int error_flag = EXIT_SUCCESS;
    size_t start = get_edge_start(edge);
    size_t end = get_edge_end(edge);

    if (start < 1 || start > point_count || end < 1 || end > point_count)
    {
        printf("Error: edge %zu-%zu is invalid\n", start, end);
        error_flag = DATA_ERROR;
    }
    
    return error_flag;
}