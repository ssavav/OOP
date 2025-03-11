#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H
#include <QGraphicsScene>

typedef struct move_data_t
{
    double dx;
    double dy;
    double dz;
} move_data_t;

typedef struct rotate_data_t
{
    double ax;
    double ay;
    double az;
} rotate_data_t;

typedef struct scale_data_t
{
    double sx;
    double sy;
    double sz;
} scale_data_t;

typedef struct draw_data_t
{
    QGraphicsScene *scene;
    double width;
    double height;
} draw_data_t;

typedef enum action_t
{
    IMPORT = 0,
    EXPORT,
    MOVE,
    ROTATE,
    SCALE,
    DRAW,
    CHECK,
    QUIT
} action_t;

typedef struct request_t
{
    action_t action;
    union
    {
        const char *filename;
        move_data_t move;
        rotate_data_t rotate;
        scale_data_t scale;
        draw_data_t draw;
    };
}request_t;

int manager(request_t request);

#endif // REQUEST_MANAGER_H
