#ifndef EDGES_H
#define EDGES_H

#include "edge.h"

typedef struct edges_t
{
    edge_t *data;
    size_t len;
} edges_t;

int edges_alloc_count(edges_t &edges, size_t count);
void edges_free(edges_t &edges);

#endif // EDGES_H
