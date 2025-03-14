#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsScene>
#include "consts.h"
#include "edge.h"
#include "edges.h"
#include "point.h"
#include "points.h"

struct figure_t
{
    points_t points;
    edges_t edges;
};

int read_figure(figure_t &figure, const char *filename);
int check_figure(figure_t &figure);
int export_figure(figure_t &figure, const char *filename);
figure_t &figure_alloc();
void figure_free(figure_t &figure);

void translate_figure(figure_t &figure, const move_data_t data);
int scale_figure(figure_t &figure, const scale_data_t data);
void rotate_figure(figure_t &figure, const rotate_data_t data);

#endif // FIGURE_H
