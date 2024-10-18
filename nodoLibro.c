#include "NodoLibro.h"


nodoLibro * crearNodoLibro(stLibro libro)
{
    nodoLibro * nuevo = (nodoLibro * )malloc(sizeof(nodoLibro));
    nuevo->libro = libro;
    nuevo->sig = NULL;
    return nuevo;
}
nodoLibro * agregarAlFinalLibro(nodoLibro * listaLibro, nodoLibro * nuevo)
{
    if(!listaLibro)
    {
        listaLibro = nuevo;
    }
    else
    {
        nodoLibro * ultimo = buscarUltimo(listaLibro);
        ultimo->sig = nuevo;
    }

    return listaLibro;
}

nodoLibro * buscarPorAutor(nodoLibro * listaLibro, char * autor)
{
    nodoLibro * seg = listaLibro;
    int flag=0;

    while(seg != NULL && flag == 0 )
    {
        if(strcmp(seg->libro.autor,autor)==0)
        {
            flag = 1;
        }
        else
        {
            seg = seg->sig;
        }
    }
    if(flag == 1)
    {
        return seg;
    }
    else
    {
        return NULL;
    }
}

nodoLibro * buscarPorTitulo(nodoLibro * listaLibro, char titulo)
{
    nodoLibro * seg = listaLibro;
    int flag = 0;

    while(seg != NULL && flag == 0 )
    {
        if(strcmp(seg->libro.titulo,titulo)==0)
        {
            flag == 1;
        }
        else
        {
            seg = seg->sig;
        }
    }
    if(flag == 1)
    {
        return seg;
    }
    else
    {
        return NULL;
    }
}


