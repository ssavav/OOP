#include "edge.h"

void set_edge(edge_t &edge, const size_t start, const size_t end)
{
    edge.start = start;
    edge.end = end;
}

int get_edge_data(FILE *file, size_t *start, size_t *end)
{
    int error_flag = EXIT_SUCCESS;
    
    if (fscanf(file, "%zu %zu", start, end) != 2)
    {
        printf("Error: invalid edge format\n");
        error_flag = DATA_ERROR;
    }
    
    return error_flag;
}

int read_edge(FILE *file, edge_t &edge)
{
    int error_flag = EXIT_SUCCESS;
    size_t start, end;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        error_flag = get_edge_data(file, &start, &end);
        if (!error_flag)
            set_edge(edge, start, end);
    }
    return error_flag;
}


int export_edge(FILE *file, const edge_t &edge)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        fprintf(file, "%zu %zu\n", edge.start, edge.end);
    }
    
    return error_flag;
}

void deepcopy_edge(edge_t &dst, const edge_t &src)
{
    dst.start = src.start;
    dst.end = src.end;
}

int check_edge(const edge_t &edge, const size_t point_count)
{
    int error_flag = EXIT_SUCCESS;

    if (edge.start < 1 || edge.start > point_count || edge.end < 1 || edge.end > point_count)
    {
        printf("Error: edge %zu-%zu is invalid\n", edge.start, edge.end);
        error_flag = DATA_ERROR;
    }
    
    return error_flag;
}

int export_edge_wrapper(FILE *file, const edge_t *data, const size_t len)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        for (size_t i = 0; !error_flag && i < len; i++)
        {
            error_flag = export_edge(file, data[i]);
        }
    }
    
    return error_flag;
}

void deep_copy_edge_wrapper(edge_t *dst_data, const edge_t *src_data, const size_t src_len)
{
    for (size_t i = 0; i < src_len; i++)
    {
        deepcopy_edge(dst_data[i], src_data[i]);
    }
}

int check_edge_wrapper(const edge_t *edges, const size_t edges_count, const size_t point_count)
{
    int error_flag = EXIT_SUCCESS;
    for (size_t i = 0; !error_flag && i < edges_count; i++)
    {
        error_flag = check_edge(edges[i], point_count);
    }
    return error_flag;
}


int read_edge_wrapper(edge_t *edges, size_t point_count, FILE *file)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        for (size_t i = 0; !error_flag && i < point_count; i++)
            error_flag = read_edge(file, edges[i]);
    }
    

    return error_flag;
}