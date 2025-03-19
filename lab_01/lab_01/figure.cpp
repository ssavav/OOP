#include "figure.h"

figure_t &figure_init()
{
    static figure_t figure;
    
    points_init(figure.points);
    edges_init(figure.edges);
    center_init(figure.center);
    
    return figure;
}

int figure_free(figure_t &figure)
{
    points_free_wrapper(figure.points);
    edges_free_wrapper(figure.edges);

    return EXIT_SUCCESS;
}

void calc_figure_center(figure_t &figure)
{
    calc_points_center(figure.center, figure.points, figure.points.len);
}

void update_figure_center(figure_t &figure)
{
    calc_figure_center(figure);
}

int deepcopy_figure(figure_t &dst, const figure_t &src)
{
    int error_flag = EXIT_SUCCESS;
    
    // figure_free(dst);
    
    error_flag = deepcopy_points(dst.points, src.points);
    if (!error_flag)
    {
        error_flag = deepcopy_edges(dst.edges, src.edges);
        if (error_flag)
            points_free_wrapper(dst.points);
    }
    
    return error_flag;
}

int open_file(FILE *&file, const char *filename, const char *mode)
{
    int error_flag = EXIT_SUCCESS;
    
    file = fopen(filename, mode);
    if (!file)
    {
        printf("Error while opening the file: %s\n", filename);
        error_flag = FILE_ERROR;
    }
    return error_flag;
}

int read_fields(figure_t &temp_figure, FILE *file)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        error_flag = read_points(temp_figure.points, file);
        if (!error_flag)
        {
            error_flag = read_edges(temp_figure.edges, file);
            if (error_flag) 
                points_free_wrapper(temp_figure.points);
        }
    }
    
    return error_flag;
}

int read_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    
    FILE *file = NULL;
    error_flag = open_file(file, filename, READ);
    
    // вынесено
    if (!error_flag)
    {
        figure_t temp_figure;// = figure_init();
        error_flag = read_fields(temp_figure, file); // поменял местами
        fclose(file);
        if (!error_flag)
        {
            error_flag = check_figure(temp_figure);

            if (!error_flag)
                error_flag = deepcopy_figure(figure, temp_figure);
            else
                figure_free(temp_figure);
        }
    }

    return error_flag;
}
int load_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = read_figure(figure, filename);
    if (!error_flag)
    {
        calc_figure_center(figure);
    }
    return error_flag;
}

int check_figure_wrapper(const points_t &points, const edges_t &edges)
{
    int error_flag = check_edges(edges, points.len);
    return error_flag;
}

int check_figure(const figure_t &figure)
{
    int error_flag = EXIT_SUCCESS;

    error_flag = check_figure_wrapper(figure.points, figure.edges);

    
    return error_flag;
}

int export_figure(figure_t &figure, const char *filename)
{
    int error_flag = EXIT_SUCCESS;
    FILE *file = NULL;
    error_flag = check_figure(figure);
    
    if (!error_flag)
    {
        error_flag = open_file(file, filename, WRITE);
        if (!error_flag)
        {
            export_points(file, figure.points);
            export_edges(file, figure.edges);
            fclose(file);
        }
    }
    
    return error_flag;
}

int translate_figure(figure_t &figure, const move_data_t data)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_figure(figure);
    if (!error_flag)
    {
        translate_points_all(figure.points, figure.center, data);
    }

    return error_flag;
}

int scale_figure(figure_t &figure, const scale_data_t data)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_figure(figure);
    if (!error_flag)
    {
        error_flag = scale_points_all(figure.points, figure.center, data);
    }

    return error_flag;
}


// добавить поворот аокруг центра а не вокруг оси
int rotate_figure(figure_t &figure, const rotate_data_t data)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_figure(figure);
    if (!error_flag)
    {
        // translate_figure_to_origin(figure.points, figure.center);
    
        rotate_points_all(figure.points, figure.center, data);
        
        // translate_figure_from_origin(figure.points, figure.center);
    }
    
    return error_flag;
}