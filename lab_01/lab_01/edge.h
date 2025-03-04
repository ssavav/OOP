#ifndef EDGE_H
#define EDGE_H

#include "consts.h"

struct edge_t
{
    int start, end;
};
struct edges_t
{
    edge_t *data;
    size_t len;
};


#endif // EDGE_H
