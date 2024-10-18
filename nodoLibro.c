#include "NodoLibro.h"
#include "Libro.h"

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
        nodoLibro * ultimo = buscarUltimoLibro(listaLibro);
        ultimo->sig = nuevo;
    }

    return listaLibro;
}

nodoLibro* buscarUltimoLibro(nodoLibro* listaLibro)
{
    nodoLibro * seg = listaLibro;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

void muestraNodoLibro(nodoLibro * nodo)
{
    muestraLibro(nodo->libro);
}

void muestraListaLibro(nodoLibro * listaLibro)
{
    while(listaLibro)
    {
        muestraNodoLibro(listaLibro);
        listaLibro = listaLibro->sig;
    }
}

void muestraUnLibroPorId(nodoLibro * listaLibro, int id){
    nodoLibro * seg = listaLibro;
    int flag = 0;
    while(seg != NULL && flag == 0){
        if(id == seg->libro.idLibro){
            flag = 1;
        }
        else{
            seg = seg->sig;
        }
    }
    if(flag == 1 ){
        muestraNodoLibro(seg);
    }
}
