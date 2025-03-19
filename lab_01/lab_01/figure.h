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
    point_t center;
};

int read_figure(figure_t &figure, const char *filename);
int load_figure(figure_t &figure, const char *filename);
int check_figure(const figure_t &figure);
int export_figure(figure_t &figure, const char *filename);
figure_t &figure_init();
int figure_free(figure_t &figure);

int translate_figure(figure_t &figure, const move_data_t data);
int scale_figure(figure_t &figure, const scale_data_t data);
int rotate_figure(figure_t &figure, const rotate_data_t data);

#endif // FIGURE_H
