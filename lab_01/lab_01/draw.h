#ifndef DRAW_H
#define DRAW_H
#include "figure.h"

typedef struct line_t
{
    point_t start;
    point_t end;
} line_t;

int draw_figure(const figure_t &figure, draw_data_t draw);

#endif // DRAW_H
