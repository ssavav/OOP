#ifndef EDGES_H
#define EDGES_H

#include "edge.h"
typedef struct edges_t
{
    edge_t *data;
    size_t len;
} edges_t;

int edges_alloc_count(edge_t *&edges, const size_t count);
edge_t get_edge(const edges_t &edges, size_t i);
void edges_free(edge_t *data);
void edges_free_wrapper(edges_t &edges);
int read_edges(edges_t &edges, FILE *file);
void edges_init(edges_t &edges);
int export_edges(FILE *file, edges_t &edges);

size_t get_edges_size(const edges_t &edges);
void set_edges_count(edges_t &edges, const size_t count);
edge_t*  get_edges_array(const edges_t &edges);
int deepcopy_edges(edges_t &dst, const edges_t &src);
int check_edges(const edges_t &edges, size_t point_count);

#endif // EDGES_H
