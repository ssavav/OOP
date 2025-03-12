#include "helpful.h"

size_t get_points_size(const points_t &points)
{
    return points.len;
}

size_t get_edges_size(const edges_t &edges)
{
    return edges.len;
}

void set_points_count(points_t &points, const size_t count)
{
    points.len = count;
}

void set_edges_count(edges_t &edges, const size_t count)
{
    edges.len = count;
}

point_t *get_points_array(points_t &points)
{
    return points.data;
}

edge_t *get_edges_array(edges_t &edges)
{
    return edges.data;
}

int get_edge_start(edge_t edge)
{
    return edge.start;
}

int get_edge_end(edge_t edge)
{
    return edge.end;
}