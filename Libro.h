#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED


typedef struct{
    int idLibro; /// �nico, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si est� activo - 1 si est� eliminado
}stLibro;


void mostrarLibro(stLibro libro);

#endif // LIBRO_H_INCLUDED
