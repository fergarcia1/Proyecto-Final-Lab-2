#include "comentario.h"
#include "stdio.h"
#include <time.h>


int randId(int min, int max) {
    // Genera un número aleatorio entre min y max (inclusive)
    return rand() % (max - min + 1) + min;
}

stComentario crearComentario(int idLibro, int idUsuario)
{
    stComentario aux;
    aux.idComentario = randId(1, 5000);
    char coment[250];
    printf("Comentario: ");
    printf("\n>");
    fflush(stdin);
    fgets(coment, sizeof(coment), stdin);
    strcpy(aux.descripcion,coment);
    aux.idLibro = idLibro;
    aux.idUsuario = idUsuario;

    return aux;
}

stComentario cambiarComentario(stComentario comentario)
{
    printf("\nNuevo comentario: ");
    printf("\n>");
    fflush(stdin);
    fgets(comentario.descripcion, sizeof(comentario.descripcion), stdin);

    return comentario;
}

stComentario eliminarComentario(stComentario comentario)
{
    printf("\nComentario eliminado con exito ");

    comentario.eliminado = -1;

    return comentario;
}

nodoComentario * crearNodoComentario(stComentario comen)
{
    nodoComentario * nuevo = (nodoComentario * )malloc(sizeof(nodoComentario));
    nuevo->coment = comen;
    nuevo->sig = NULL;
    return nuevo;
}

nodoComentario* buscarUltimoComentario(nodoComentario* lista)
{
    nodoComentario * seg = lista;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

nodoComentario* agregarAlFinalComentario(nodoComentario* lista, nodoComentario* nuevo)
{
    if(!lista)
    {
        lista = nuevo;
    }
    else
    {
        nodoComentario* ultimo = buscarUltimoComentario(lista);
        ultimo->sig = nuevo;
    }

    return lista;
}

void mostrarListaComentarios(nodoComentario * lista)
{
     while(lista)
    {
        if(lista->coment.idComentario != 0){
                if(lista->coment.eliminado != -1)
                {
                    muestraUnComentario(lista->coment);
                }
        }
        lista = lista->sig;
    }
}

void mostrarListaComentariosPorId(nodoComentario * lista,int id)
{
    int flag = 0;
     while(lista)
    {
        if(lista->coment.idComentario != 0){
                if(lista->coment.eliminado != -1)
                {
                    if(lista->coment.idUsuario == id)
                    {
                        muestraUnComentario(lista->coment);
                        flag = 1;
                    }
                }
        }
        lista = lista->sig;
    }
    if(flag == 0)
    {
        printf("No se encontraron comentarios suyos en este libro");
        system("pause");
    }
}

void muestraUnComentario(stComentario a)
{
    printf("\n-----------------------\n");
    printf("Id Comentario: %i", a.idComentario);
    printf(" (Id Usuario %i)\n", a.idUsuario);
    printf("Comentario: %s\n", a.descripcion);
}

nodoComentario * darDeBajaComentario(nodoComentario * listaComentario)
{
    int idBorrar = 0, flag = 0;
    mostrarListaComentarios(listaComentario);
    nodoComentario * seg = listaComentario;
    nodoComentario * comentarioBaja = NULL;
    printf("\n-----------------------\n");
    printf("Id del comentario a dar de baja");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBorrar);
    while(seg && flag == 0)
    {
        if(seg->coment.idComentario == idBorrar)
        {
            flag = 1;
        }
        seg = seg->sig;
    }
    if(flag = 0) ///verifico que la id se haya encontrado
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeBajaComentario(listaComentario);
    }
    else
    {
        comentarioBaja = buscarIdComentario(listaComentario,idBorrar); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(comentarioBaja)
        {
            comentarioBaja->coment.eliminado = -1;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja libro.");
        }
    }
    return listaComentario;
}

nodoComentario * buscarIdComentario(nodoComentario * listaComentario, int idBorrar)
{
    nodoComentario * seg = listaComentario;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(seg->coment.idComentario == idBorrar)
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

nodoComentario * darDeAltaComentario(nodoComentario * listaComentario)
{
    int idBorrar = 0, flag = 0;
    muestraListaComentarioBaja(listaComentario);
    nodoComentario * seg = listaComentario;
    nodoComentario * comentarioAlta = NULL;
    printf("\n-----------------------\n");
    printf("Id del comentario a dar de alta");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBorrar);
    while(seg && flag == 0)
    {
        if(seg->coment.idComentario == idBorrar)
        {
            flag = 1;
        }
        seg = seg->sig;
    }
    if(flag = 0) ///verifico que la id se haya encontrado
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeAltaComentario(listaComentario);
    }
    else
    {
        comentarioAlta = buscarIdComentario(listaComentario,idBorrar); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(comentarioAlta)
        {
            comentarioAlta->coment.eliminado = 0;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja libro.");
        }
    }
    return listaComentario;
}

void muestraListaComentarioBaja(nodoComentario * listaComentario)
{
    while(listaComentario)
    {
        if(listaComentario->coment.eliminado == -1)
        {
            muestraUnComentario(listaComentario->coment);
        }
        listaComentario = listaComentario->sig;
    }
}

void modificarComentariosPropios(nodoLibro * ldl, int idUsuario,int idLibroActual)
{
    int idBuscar = 0;
    system("cls");
    printf("Id del libro en el que desea modificar un comentario (-1 para volver atras!)");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBuscar);
    if(idBuscar == -1 && idBuscar < idLibroActual)
    {
        printf("\nId Invalido!\n");
        system("pause");
        modificarComentariosPropios(ldl,idUsuario,idLibroActual);
    }
    nodoLibro * libroABuscar = buscarIdLibro(ldl,idBuscar);
    nodoComentario * comentarioAcambiar = NULL;
    mostrarListaComentariosPorId(libroABuscar->coment,idUsuario);
    printf("Id del comentario que desea modificar");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBuscar);
    comentarioAcambiar = buscarIdComentario(libroABuscar->coment,idBuscar);
    comentarioAcambiar->coment = cambiarComentario(comentarioAcambiar->coment);
}

void eliminarComentariosPropios(nodoLibro * ldl, int idUsuario,int idLibroActual)
{
    int idBuscar = 0;
    system("cls");
    printf("Id del libro en el que desea elimnar un comentario (-1 para volver atras!)");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBuscar);
    if(idBuscar == -1 && idBuscar < idLibroActual)
    {
        printf("\nId Invalido!\n");
        system("pause");
        eliminarComentariosPropios(ldl,idUsuario,idLibroActual);
    }
    nodoLibro * libroABuscar = buscarIdLibro(ldl,idBuscar);
    nodoComentario * comentarioAeliminar = NULL;
    mostrarListaComentariosPorId(libroABuscar->coment,idUsuario);
    printf("Id del comentario que desea eliminar");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBuscar);
    comentarioAeliminar = buscarIdComentario(libroABuscar->coment,idBuscar);
    comentarioAeliminar->coment = eliminarComentario(comentarioAeliminar->coment);
}
