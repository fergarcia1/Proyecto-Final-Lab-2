#ifndef NODOUSUARIO_H_INCLUDED
#define NODOUSUARIO_H_INCLUDED

#include "Usuario.h"
#include <conio.h>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    stUsuario usuario;
    struct nodoUsuario* sig;
} nodoUsuario;

nodoUsuario * inicLista();
nodoUsuario * buscarMailUsuario(nodoUsuario* listaUsuarios, char * mail); /// deberia retornar NULL si no se encuentra el mail
nodoUsuario * crearNodoUsuario(stUsuario usuario);
nodoUsuario * agregarAlFinalUsuario(nodoUsuario* lista, nodoUsuario * nuevo);
nodoUsuario * buscarUltimo(nodoUsuario* listaUsuarios);
void muestraNodo(nodoUsuario * nodo);
void muestraLista(nodoUsuario * listaUsuario);
nodoUsuario* buscarIdUsuario(nodoUsuario* listaUsuarios, int idBorrar);

#endif // NODOUSUARIO_H_INCLUDED
