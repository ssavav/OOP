#ifndef EDGE_H
#define EDGE_H

#include "consts.h"

struct edge_t
{
    int start, end;
};


void set_edge(edge_t &edge, const size_t start, const size_t end);
int get_edge_start(edge_t edge);
int get_edge_end(edge_t edge);
int read_edge(FILE *file, edge_t &edge);
int export_edge(FILE *file, const edge_t &edge);
void deepcopy_edge(edge_t &dst, const edge_t &src);
int check_edge(const edge_t &edge, const size_t point_count);

int export_edge_wrapper(FILE *file, const edge_t *data, const size_t len);
void deep_copy_edge_wrapper(edge_t *dst_data, const edge_t *src_data, const size_t src_len);
int check_edge_wrapper(const edge_t *edges, const size_t edges_count, const size_t point_count);
int read_edge_wrapper(edge_t *edges, size_t point_count, FILE *file);

// int check_file_opened(FILE *file);

#endif // EDGE_H
