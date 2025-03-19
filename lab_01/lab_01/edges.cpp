#include "edges.h"



void edges_free(edge_t *data)
{
    free(data);
}
void edges_free_wrapper(edges_t &edges)
{
    edges_free(edges.data);
}

int edges_alloc_count(edge_t *&edges, const size_t count)
{
    int error_flag = EXIT_SUCCESS;
    edges = (edge_t*)malloc(sizeof(edge_t) * count);
    if (!edges)
        error_flag = MEMORY_ERROR;

    return error_flag;
}

void edges_init(edges_t &edges)
{
    edges.data = NULL;
    edges.len = 0;
}

int read_edges_count(size_t &edge_count, FILE *file)
{
    // char line[BUFSIZ];
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        if (fscanf(file, "%zu", &edge_count) != 1)
        {
            printf("Error: invalid edge count format\n");
            error_flag = DATA_ERROR;
        }
    }
    return error_flag;
}

// int read(edges_t &edges, FILE *file)
// {
//     int error_flag = EXIT_SUCCESS;
//     error_flag = check_file_opened(file);
//     if (!error_flag)
//     {
//         error_flag = read_edge_wrapper(edges.data, edges.len, file);
        
//         if (error_flag)
//         {
//             edges_clear(edges);
//         }
//     }
//     return error_flag;
// }

int read_edges(edges_t &edges, FILE *file)
{
    int error_flag = EXIT_SUCCESS;
    // char line[BUFSIZ];
    size_t edge_count = 0;

    if (check_file_opened(file))
    {
        return FILE_ERROR;
    }
    
    
    error_flag = read_edges_count(edges.len, file);
        if (!error_flag)
        {
            error_flag = edges_alloc_count(edges.data, edges.len);
            if (!error_flag)
            {
                error_flag = read_edge_wrapper(edges.data, edges.len, file);
        
                if (error_flag)
                {
                    edges_free(edges.data);
                }
            }
        }
    
    return error_flag;
}

int export_edges(FILE *file, edges_t &edges)
{
    int error_flag = EXIT_SUCCESS;
    error_flag = check_file_opened(file);
    if (!error_flag)
    {
        fprintf(file, "%zu\n", edges.len);
        error_flag = export_edge_wrapper(file, edges.data, edges.len);
    }
    
    return error_flag;
}

int deepcopy_edges(edges_t &dst, const edges_t &src)
{
    int error_flag = EXIT_SUCCESS;
    
    error_flag = edges_alloc_count(dst.data, src.len);
    if (!error_flag)
    {
        dst.len = src.len; 
        deep_copy_edge_wrapper(dst.data, src.data, src.len);
    }
    
    return error_flag;
}

int check_edges(const edges_t &edges, const size_t point_count)
{
    int error_flag = EXIT_SUCCESS;
    if (edges.len == 0 || point_count == 0)
        error_flag = DATA_ERROR;
    else
        error_flag = check_edge_wrapper(edges.data, edges.len, point_count);
    

    return error_flag;
}