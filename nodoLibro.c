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
