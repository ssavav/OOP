#ifndef EDGE_H
#define EDGE_H

#include "consts.h"

struct edge_t
{
    int start, end;
};


void set_edge(edge_t &edge, const size_t start, const size_t end);

#endif // EDGE_H
