#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED


typedef struct{
    int idLibro; /// único, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stLibro;


void mostrarLibro(stLibro libro);

#endif // LIBRO_H_INCLUDED
