#include "edges.h"

void edges_free(edges_t &edges)
{
    free(edges.data);
    edges.len = 0;
}

int edges_alloc_count(edges_t &edges, size_t count)
{
    int error_flag = EXIT_SUCCESS;
    edges.data = (edge_t*)malloc(sizeof(edge_t) * count);
    if (!edges.data)
        error_flag = MEMORY_ERROR;

    edges.len = count;
    return error_flag;
}