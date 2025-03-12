#ifndef HELPFUL_H
#define HELPFUL_H
#include "figure.h"

size_t get_points_size(const points_t &points);
size_t get_edges_size(const edges_t &edges);

void set_points_count(points_t &points, const size_t count);
void set_edges_count(edges_t &edges, const size_t count);

point_t* get_points_array(points_t &points);
edge_t*  get_edges_array(edges_t &edges);

int get_edge_start(edge_t edge);
int get_edge_end(edge_t edge);

#endif // HELPFUL_H
