#ifndef FIGURE_H
#define FIGURE_H

#include "consts.h"
#include "edge.h"
#include "point.h"
#include <QGraphicsScene>

struct figure_t
{
    points_t points;
    edges_t edges;
};

int read_figure(const char *filename, figure_t &figure);
int check_figure(figure_t &figure);
int export_figure(const char *filename, figure_t &figure);

#endif // FIGURE_H
