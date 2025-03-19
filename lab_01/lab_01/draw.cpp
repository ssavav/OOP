#include "draw.h"
#include "mainwindow.h"

double to_scene_x(const double x, const double sceneWidth) 
{
    return x + sceneWidth / 2;
}

double to_scene_y(const double y, const double sceneHeight)
{
    return y + sceneHeight / 2;
}

void to_scene_point(point_t &point, const double width, const double height)
{
    point.x = to_scene_x(point.x, width);
    point.y = to_scene_y(point.y, height);
}

void to_scene_line(line_t &line, const double width, const double height)
{
    to_scene_point(line.start, width, height);
    to_scene_point(line.end, width, height);
}

int scene_draw_line_wrapper(QGraphicsScene *scene, const point_t &start, const point_t &end)
{
    int error_flag = EXIT_SUCCESS;
    if (!scene)
        error_flag =  SCENE_ERROR;
    else
        scene->addLine(start.x, start.y, end.x, end.y, QPen(Qt::black, 1.5));

    return error_flag;
}

// int scene_draw_line(line_t line, QGraphicsScene *scene)
int scene_draw_line(line_t line, draw_data_t data)
{
    int error_flag = EXIT_SUCCESS;
    if (!data.scene)
        error_flag =  SCENE_ERROR;
    else
        scene_draw_line_wrapper(data.scene, line.start, line.end);
        
    return error_flag;
}

int draw_line(line_t line, const draw_data_t data)
{
    int error_flag = EXIT_SUCCESS;

    to_scene_line(line, data.width, data.height);
    // error_flag = scene_draw_line(line, data.scene);
    error_flag = scene_draw_line(line, data);

    return error_flag;
}

int create_line(line_t &line, const points_t &points, const edge_t edge)
{   
    int error_flag = EXIT_SUCCESS;
    error_flag = check_edge(edge, points.len);
    if (!error_flag)
    {
        int start_idx = edge.start - 1;
        int end_idx = edge.end - 1;
        line.start = get_point(points, start_idx);
        line.end = get_point(points, end_idx);
    }

    return error_flag;
}

int draw_line_wrapper(const draw_data_t draw,const size_t len, const edge_t *data, const points_t &points)
{
    int error_flag = EXIT_SUCCESS;
    line_t line;
    for (size_t i = 0; !error_flag && i < len; i++)
    {
        error_flag = create_line(line, points, data[i]);
        if (!error_flag)
        {
            error_flag = draw_line(line, draw);
        }
    }
    return error_flag;
}

int draw_lines(draw_data_t draw, const edges_t &edges, const points_t &points)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = draw_line_wrapper(draw, edges.len, edges.data, points);
    return error_flag;
}

void clear_scene(QGraphicsScene *scene)
{
    scene->clear();
}

int draw_figure(const figure_t &figure, draw_data_t draw)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_figure(figure);
    if (!error_flag)
    {
        // обернуто в функцию
        clear_scene(draw.scene);
        error_flag = draw_lines(draw, figure.edges, figure.points);
    }

    return error_flag;
}