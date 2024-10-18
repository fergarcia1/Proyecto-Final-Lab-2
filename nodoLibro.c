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
        if(listaLibro->libro.eliminado == 0)
        {
            muestraNodoLibro(listaLibro);
        }
        listaLibro = listaLibro->sig;
    }
}

void muestraListaLibroBaja(nodoLibro * listaLibro)
{
    while(listaLibro)
    {
        if(listaLibro->libro.eliminado == -1)
        {
            muestraNodoLibro(listaLibro);
        }
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
        if(compararCadenasIgnorandoMayusculas(aux, seg->libro.autor) == 1)
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
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
    printf("\nCategoria por la cual desea filtrar los libros (Aventura, Drama, Ciencia ficcion, Clasicos, Romance, Ficcion, Suspenso)");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
    printf("\n>");
    fflush(stdin);
    gets(aux);
    printf("\n");
    nodoLibro * seg = listaLibro;
    int flag = 0;
    while(seg != NULL)
    {
        if(compararCadenasIgnorandoMayusculas(aux, seg->libro.autor) == 1)
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

nodoLibro * darDeBajaLibro(nodoLibro * listaLibro,int idLibroActual)
{
    int idBorrar = 0;
    muestraListaLibro(listaLibro);
    printf("\n-----------------------\n");
    printf("Id del libro a dar de baja");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBorrar);
    if(idBorrar > idLibroActual || idBorrar < 0) ///verifico que la id este entre 0 y las id validas
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeBajaLibro(listaLibro,idLibroActual);
    }
    else
    {
        nodoLibro * libroBaja = buscarIdLibro(listaLibro,idBorrar); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(libroBaja)
        {
            libroBaja->libro.eliminado = -1;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja libro.");
        }
    }
    return listaLibro;
}

nodoLibro * darDeAltaLibro(nodoLibro * listaLibro,int idLibroActual)
{
    system("cls");
    int idSubir = 0;
    muestraListaLibroBaja(listaLibro);
    printf("\n-----------------------\n");
    printf("Id del libro a dar de alta");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idSubir);
    if(idSubir > idLibroActual || idSubir < 0) ///verifico que la id este entre 0 y las id validas
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeAltaLibro(listaLibro,idLibroActual);
    }
    else
    {
        nodoLibro * libroAlta = buscarIdLibro(listaLibro,idSubir); ///libroBaja va a ser igual al nodo devuelto por buscarIdLibro (NULL si no esta en la lista)
        if(libroAlta)
        {
            libroAlta->libro.eliminado = 0;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja usuario.");
        }
    }
    return listaLibro;
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




