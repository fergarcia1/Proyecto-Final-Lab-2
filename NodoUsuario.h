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
nodoUsuario * buscarUltimoUsuario(nodoUsuario* listaUsuarios);
void muestraNodoUsuario(nodoUsuario * nodo);
void muestraListaUsuario(nodoUsuario * listaUsuario);
nodoUsuario* buscarIdUsuario(nodoUsuario* listaUsuarios, int idBorrar); ///retorno NULL si no se encuentra el usuario

#endif // NODOUSUARIO_H_INCLUDED
