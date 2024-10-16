#include "NodoUsuario.h"

nodoUsuario * inicLista(){
    return NULL;
}

nodoUsuario* buscarMailUsuario(nodoUsuario* listaUsuarios, char * mail){
    nodoUsuario * seg = listaUsuarios;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(strcmp(seg->usuario.email, mail) == 0){
            flag = 1;
        }
        else{
            seg = seg->sig;
        }
    }
    if(flag == 1 ){
        return seg;
    }
    else{
        return NULL;
    }
}

nodoUsuario * crearNodoUsuario(stUsuario usuario)
{
    nodoUsuario * nuevo = (nodoUsuario * )malloc(sizeof(nodoUsuario));
    nuevo->usuario = usuario;
    nuevo->sig = NULL;
    return nuevo;
}

nodoUsuario* buscarUltimo(nodoUsuario* listaUsuarios)
{
    nodoUsuario * seg = listaUsuarios;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

nodoUsuario* agregarAlFinalUsuario(nodoUsuario* listaUsuarios, nodoUsuario * nuevo)
{
    if(!listaUsuarios)
    {
        listaUsuarios = nuevo;
    }
    else
    {
        nodoUsuario * ultimo = buscarUltimo(listaUsuarios);
        ultimo->sig = nuevo;
    }

    return listaUsuarios;
}

void muestraNodo(nodoUsuario * nodo)
{
    muestraUnUsuario(nodo->usuario);

}

void muestraLista(nodoUsuario * listaUsuario)
{
    while(listaUsuario)
    {
        muestraNodo(listaUsuario);
        listaUsuario = listaUsuario->sig;
    }
}

nodoUsuario* buscarIdUsuario(nodoUsuario* listaUsuarios, int idBorrar){
    nodoUsuario * seg = listaUsuarios;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(seg->usuario.idUsuario == idBorrar){
            flag = 1;
        }
        else{
            seg = seg->sig;
        }
    }
    if(flag == 1 ){
        return seg;
    }
    else{
        return NULL;
    }
}

