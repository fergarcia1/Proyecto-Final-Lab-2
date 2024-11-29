#ifndef COMENTARIO_H_INCLUDED
#define COMENTARIO_H_INCLUDED

#include "string.h"
#include "NodoLibro.h"
typedef struct {
    int idComentario;  /// �nico, autoincremental
    int idLibro;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20]; /// o se puede hacer con dia, mes, anio.
    int eliminado; /// 0 si est� activo - 1 si est� eliminado
}stComentario;

typedef struct{
    stComentario coment;
    struct nodoComentario * sig;
}nodoComentario;

stComentario  crearComentario(int idLibro, int idUsuario);
nodoComentario * crearNodoComentario(stComentario comentario);
nodoComentario* buscarUltimoComentario(nodoComentario* lista);
nodoComentario* agregarAlFinalComentario(nodoComentario* lista, nodoComentario* nuevo);
void mostrarListaComentarios(nodoComentario * lista);
void muestraUnComentario(stComentario a);
nodoComentario * buscarIdComentario(nodoComentario * listaComentario, int idBorrar);

#endif // COMENTARIO_H_INCLUDED
