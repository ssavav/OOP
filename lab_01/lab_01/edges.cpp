#include "edges.h"

edge_t get_edge(const edges_t &edges, const size_t i)
{
    return edges.data[i];
}

size_t get_edges_size(const edges_t &edges)
{
    return edges.len;
}

void set_edges_count(edges_t &edges, const size_t count)
{
    edges.len = count;
}

edge_t *get_edges_array(const edges_t &edges)
{
    return edges.data;
}

void edges_free(edges_t &edges)
{
    free(edges.data);
    edges.len = 0;
}

int edges_alloc_count(edges_t &edges, const size_t count)
{
    int error_flag = EXIT_SUCCESS;
    edges.data = (edge_t*)malloc(sizeof(edge_t) * count);
    if (!edges.data)
        error_flag = MEMORY_ERROR;
    else
        edges.len = count;

    return error_flag;
}

void edges_init(edges_t &edges)
{
    edges.data = NULL;
    edges.len = 0;
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
        error_flag = read_edge(file, edges.data[i], error_flag);
        if (error_flag != EXIT_SUCCESS)
        {
            edges_free(edges);
        }
    }

    return error_flag;
}

void export_edges(FILE *file, edges_t &edges)
{
    size_t e_count = get_edges_size(edges);
    edge_t *edges_arr = get_edges_array(edges);

    fprintf(file, "e %zu\n", e_count);
    for (size_t i = 0; i < e_count; i++)
    {
        export_edge(file, edges_arr[i]);
    }
}

int deepcopy_edges(edges_t &dst, const edges_t &src)
{
    int error_flag = EXIT_SUCCESS;
    
    error_flag = edges_alloc_count(dst, src.len);
    
    for (size_t i = 0; !error_flag && i < src.len; i++)
    {
        deepcopy_edge(dst.data[i], src.data[i]);
    }
    
    return error_flag;
}

int check_edges(const edges_t &edges, const size_t point_count)
{
    int error_flag = EXIT_SUCCESS;
    size_t edge_count = get_edges_size(edges);
    
    if (edge_count == 0)
        error_flag = DATA_ERROR;
        
    edge_t *edges_array = get_edges_array(edges);
    for (size_t i = 0; !error_flag && i < edge_count; i++)
    {
        error_flag = check_edge(edges_array[i], point_count);
    }
    return error_flag;
}