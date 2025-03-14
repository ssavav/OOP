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
int read_edge(FILE *file, edge_t &edge, int &error_flag);
int export_edge(FILE *file, const edge_t &edge);
void deepcopy_edge(edge_t &dst, const edge_t &src);
int check_edge(const edge_t &edge, const size_t point_count);

#endif // EDGE_H
