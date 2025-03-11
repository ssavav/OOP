#include "request_manager.h"
#include "figure.h"
#include "draw.h"

int manager(request_t request)
{
    static figure_t figure = figure_alloc();
    int error = EXIT_SUCCESS;

    switch (request.action)
    {
    case IMPORT:
        error = read_figure(figure, request.filename);
        break;
    case EXPORT:
        error = export_figure(figure, request.filename);
        break;
    case MOVE:
        translate_points(figure.points, request.move);
        break;
    case SCALE:
        error = scale_points(figure.points, request.scale);
        break;
    case ROTATE:
        rotate_points(figure.points, request.rotate);
        break;
    case DRAW:
        draw_figure(request.draw, figure);
        break;
    case CHECK:
        error = check_figure(figure);
        break;
    case QUIT:
        figure_free(figure);
        break;
    }
    
    return error;
}

