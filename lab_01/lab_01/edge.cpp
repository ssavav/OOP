#include "edge.h"

int edges_alloc(edges_t &edges)
{
    int error = EXIT_SUCCESS;
    edges.data = (edge_t*)malloc(sizeof(edge_t) * MAX_VERTICES);
    if (!edges.data)
    {
        error = MEMORY_ERROR;
    }
    return error;
}

void edges_free(edges_t &edges)
{
    free(edges.data);
}