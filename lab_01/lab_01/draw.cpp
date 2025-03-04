#include "figure.h"
#include "draw.h"
#include "mainwindow.h"

// void draw_figure(QGraphicsScene *scene, const figure_t &figure)
// {
//     scene->clear();

//     QRectF rect = scene->sceneRect();
//     double sceneWidth  = rect.width();
//     double sceneHeight = rect.height();

//     for (size_t i = 0; i < figure.edges.len; i++)
//     {
//         int start_idx = figure.edges.data[i].start - 1;
//         int end_idx   = figure.edges.data[i].end - 1;
//         double x1 = figure.points.data[start_idx].x + sceneWidth / 2;
//         double y1 = figure.points.data[start_idx].y + sceneHeight / 2;
//         double x2 = figure.points.data[end_idx].x + sceneWidth / 2;
//         double y2 = figure.points.data[end_idx].y + sceneHeight / 2;
//         scene->addLine(x1, y1, x2, y2, QPen(Qt::black, 1.5));
//     }
// }

size_t get_edges_count(const edges_t &edges)
{
    return edges.len;
}

edge_t get_edge(const edges_t &edges, size_t i)
{
    return edges.data[i];
}

size_t get_points_count(const points_t &points)
{
    return points.len;
}

point_t get_point(const points_t &points, const int index)
{
    return points.data[index];
}

double to_scene_x(const double x, const double sceneWidth) {
    return x + sceneWidth / 2;
}

double to_scene_y(const double y, const double sceneHeight)
{
    return y + sceneHeight / 2;
}

void draw_figure(QGraphicsScene *scene, const figure_t &figure) {
    scene->clear();

    QRectF rect = scene->sceneRect();
    double sceneWidth  = rect.width();
    double sceneHeight = rect.height();

    size_t edges_count = get_edges_count(figure.edges);
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

        scene->addLine(x1, y1, x2, y2, QPen(Qt::black, 1.5));
    }
}
