#include "helpful.h"
#include "draw.h"
#include "mainwindow.h"

edge_t get_edge(const edges_t &edges, size_t i)
{
    return edges.data[i];
}

point_t get_point(const points_t &points, const int index)
{
    return points.data[index];
}

double to_scene_x(const double x, const double sceneWidth) 
{
    return x + sceneWidth / 2;
}

double to_scene_y(const double y, const double sceneHeight)
{
    return y + sceneHeight / 2;
}

void draw_figure(draw_data_t draw, const figure_t &figure)
{
    draw.scene->clear();

    double sceneWidth  = draw.width;
    double sceneHeight = draw.height;

    size_t edges_count = get_edges_size(figure.edges);
    for (size_t i = 0; i < edges_count; i++) {
        edge_t edge = get_edge(figure.edges, i);

        int start_idx = edge.start - 1;
        int end_idx   = edge.end - 1;

        point_t start_point = get_point(figure.points, start_idx);
        point_t end_point   = get_point(figure.points, end_idx);

        double x1 = to_scene_x(start_point.x, sceneWidth);
        double y1 = to_scene_y(start_point.y, sceneHeight);
        double x2 = to_scene_x(end_point.x, sceneWidth);
        double y2 = to_scene_y(end_point.y, sceneHeight);

        draw.scene->addLine(x1, y1, x2, y2, QPen(Qt::black, 1.5));
    }
}
