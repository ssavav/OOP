#include "model.h"

point_t vertices[MAX_VERTICES];
edge_t edges[MAX_EDGES];

int vertex_count = 0;
int edge_count = 0;

int read_model(const char *filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "Error, while opening file " << filename << std::endl;
        return FILE_ERROR;
    }

    char type;
    while (file >> type)
    {
        if (type == 'v')
        {
            if (vertex_count >= MAX_VERTICES)
            {
                std::cout << "Error, too many vertices in file" << std::endl;
                file.close();
                return TOO_MANY_VERTICES;
            }
            file >> vertices[vertex_count].x >> vertices[vertex_count].y >> vertices[vertex_count].z;
            vertex_count++;
        }
        else if (type == 'e')
        {
            if (edge_count >= MAX_EDGES)
            {
                std::cout << "Error, too many edges in file" << std::endl;
                file.close();
                return TOO_MANY_EDGES;
            }
            file >> edges[edge_count].start >> edges[edge_count].end;
        }
    }

    file.close();
    return EXIT_SUCCESS;
}

void translate_model(const double dx, const double dy, const double dz)
{
    for (int i = 0; i < vertex_count; i++)
    {
        vertices[i].x += dx;
        vertices[i].y += dy;
        vertices[i].z += dz;
    }
}

void scale_model(const double scale)
{
    for (int i = 0; i < vertex_count; i++)
    {
        vertices[i].x *= scale;
        vertices[i].y *= scale;
        vertices[i].z *= scale;
    }
}

double to_rad(const double angle)
{
    return (angle * PI / 180.0);
}

// Функция поворота вокруг оси X
void rotate_model_x(double angle) {
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (int i = 0; i < vertex_count; i++) {
        double y_new = vertices[i].y * cos_a + vertices[i].z * sin_a;
        double z_new = vertices[i].z * cos_a - vertices[i].y * sin_a;
        
        vertices[i].y = y_new;
        vertices[i].z = z_new;
    }
}

// Функция поворота вокруг оси Y
void rotate_model_y(double angle) {
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);
    
    for (int i = 0; i < vertex_count; i++) {
        double x_new = vertices[i].x * cos_a - vertices[i].z * sin_a;
        double z_new = vertices[i].x * sin_a + vertices[i].z * cos_a;
        
        vertices[i].x = x_new;
        vertices[i].z = z_new;
    }
}

// Функция поворота вокруг оси Z
void rotate_model_z(double angle) {
    double radians = to_rad(angle);
    double cos_a = cos(radians);
    double sin_a = sin(radians);

    for (int i = 0; i < vertex_count; i++) {
        double x_new = vertices[i].x * cos_a + vertices[i].y * sin_a;
        double y_new = vertices[i].y * cos_a - vertices[i].x * sin_a;

        vertices[i].x = x_new;
        vertices[i].y = y_new;
    }
}


