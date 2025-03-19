#include "request_manager.h"
#include "figure.h"
#include "draw.h"

// добавить поворот вокруг центра а не вокруг оси какой то
// дальше в рид и дроу
int manager(request_t request)
{
    static figure_t figure = figure_init();
    int error = EXIT_SUCCESS;

    // везде добавить ерроры
    switch (request.action)
    {
    case IMPORT:
        error = load_figure(figure, request.filename);
        break;
    case EXPORT:
        error = export_figure(figure, request.filename);
        break;
    case MOVE:
        error = translate_figure(figure, request.move);
        break;
    case SCALE:
        error = scale_figure(figure, request.scale);
        break;
    case ROTATE:
        error = rotate_figure(figure, request.rotate);
        break;
    case DRAW:
        error = draw_figure(figure, request.draw);
        break;
    case QUIT:
        error = figure_free(figure);
        break;
    }
    
    return error;
}

