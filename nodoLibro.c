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

void muestraUnLibroPorId(nodoLibro * listaLibro, int id)
{
    nodoLibro * seg = listaLibro;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(id == seg->libro.idLibro)
        {
            flag = 1;
        }
        else
        {
            seg = seg->sig;
        }
    }
    if(flag == 1 )
    {
        muestraNodoLibro(seg);
    }
}

nodoLibro * buscarIdLibro(nodoLibro * listaLibro, int idBorrar)
{
    nodoLibro * seg = listaLibro;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(seg->libro.idLibro == idBorrar)
        {
            flag = 1;
        }
        else
        {
            seg = seg->sig;
        }
    }
    if(flag == 1 )
    {
        return seg; ///retorno el nodo si lo encuentro
    }
    else
    {
        return NULL;
    }
}

void muestraLibroPorAutor(nodoLibro * listaLibro)
{
    char aux[20];
    system("cls");
    printf("\n-------------------------------------------------------------------");
    printf("\nAutor por el cual desea filtrar los libros (ejemplo: Toni Morrison)");
    printf("\n-------------------------------------------------------------------");
    printf("\n>");
    fflush(stdin);
    gets(aux);
    nodoLibro * seg = listaLibro;
    int flag = 0;
    while(seg != NULL)
    {
        if(strcmp(aux, seg->libro.autor) == 0)
        {
            muestraNodoLibro(seg);
            flag = 1;
        }
        seg = seg->sig;
    }
    if (!flag)
    {
        printf("No se encontraron libros del autor: %s\n", aux);
    }
}

void muestraLibroPorCategoria(nodoLibro * listaLibro)
{
    char aux[20];
    system("cls");
    printf("\n------------------------------------------------------------------");
    printf("\nCategoria por la cual desea filtrar los libros (Aventura, Drama, Ciencia ficcion, Clasicos, Romance, Ficcion, Suspenso)");
    printf("\n------------------------------------------------------------------");
    printf("\n>");
    fflush(stdin);
    gets(aux);
    printf("\n");
    nodoLibro * seg = listaLibro;
    int flag = 0;
    while(seg != NULL)
    {
        if(strcmp(aux, seg->libro.categoria) == 0)
        {
            muestraNodoLibro(seg);
            flag = 1;
        }
        seg = seg->sig;
    }
    if (!flag)
    {
        printf("No se encontraron libros de esa categoria: %s\n", aux);
    }
}
