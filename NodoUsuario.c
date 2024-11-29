#include "NodoUsuario.h"


nodoUsuario *inicArbol()
{
    return NULL;
}

nodoUsuario * CrearNodoArbol(stUsuario usuario)
{
    nodoUsuario *nuevo = (nodoUsuario *)malloc(sizeof(nodoUsuario));
    nuevo->usuario = usuario;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

nodoUsuario * InsertarNodoArbol(nodoUsuario *arbol, stUsuario usuario)
{
    if (arbol == NULL)
    {
        return CrearNodoArbol(usuario);
    }
    if (usuario.idUsuario < arbol->usuario.idUsuario)
    {
        arbol->izq = InsertarNodoArbol(arbol->izq, usuario);
    }
    else if (usuario.idUsuario > arbol->usuario.idUsuario)
    {
        arbol->der = InsertarNodoArbol(arbol->der, usuario);
    }
    return arbol;
}

nodoUsuario* buscarMailUsuario(nodoUsuario* arbolUsuarios, char *mail)
{
    if (arbolUsuarios == NULL)
    {
        return NULL; // Si el árbol está vacío o llegamos a una hoja, devolvemos NULL
    }

    if (strcmp(arbolUsuarios->usuario.email, mail) == 0)
    {
        return arbolUsuarios; // Si encontramos el correo, devolvemos el nodo
    }

    // Buscamos en los subárboles izquierdo y derecho
    nodoUsuario *resultado = buscarMailUsuario(arbolUsuarios->izq, mail);
    if (resultado == NULL)
    {
        resultado = buscarMailUsuario(arbolUsuarios->der, mail);
    }

    return resultado; // Devolvemos el nodo encontrado o NULL si no existe
}

nodoUsuario *buscarPorID(nodoUsuario *arbol, int id)
{
    if (arbol == NULL || arbol->usuario.idUsuario == id)
    {
        return arbol;
    }
    if (id < arbol->usuario.idUsuario)
    {
        return buscarPorID(arbol->izq, id);
    }
    else
    {
        return buscarPorID(arbol->der, id);
    }
}

void mostrarArbolInOrder(nodoUsuario *arbol)
{
    if (arbol)
    {
        mostrarArbolInOrder(arbol->izq);
        if (arbol->usuario.eliminado == 0)
        {
            muestraUnUsuario(arbol->usuario);
        }
        mostrarArbolInOrder(arbol->der);
    }
}



nodoUsuario* darDeBajaUsuario(nodoUsuario *arbol, int idUsuarioActual)
{
    int idBorrar = 0;
    mostrarArbolInOrder(arbol);
    printf("\n-----------------------\n");
    printf("Id del usuario a dar de baja");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBorrar);
    if(idBorrar > idUsuarioActual || idBorrar < 0) ///verifico que la id este entre 0 y las id validas
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeBajaUsuario(arbol,idUsuarioActual);
    }
    else
    {
        nodoUsuario * userBaja = buscarPorID(arbol,idBorrar); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(userBaja)
        {
            userBaja->usuario.eliminado = -1;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja usuario.");
        }
    }
    return arbol;
}


nodoUsuario * darDeAltaUsuario(nodoUsuario *arbol, int idUsuarioActual)
{
    system("cls");
    int idSubir = 0;
    mostrarArbolInOrder(arbol);
    printf("\n-----------------------\n");
    printf("Id del usuario a dar de alta");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idSubir);
    if(idSubir > idUsuarioActual || idSubir < 0) ///verifico que la id este entre 0 y las id validas
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeAltaUsuario(arbol,idUsuarioActual);
    }
    else
    {
        nodoUsuario * userAlta = buscarPorID(arbol,idSubir); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(userAlta)
        {
            userAlta->usuario.eliminado = 0;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja usuario.");
        }
    }
    return arbol;
}

nodoUsuario* buscarUltimoUsuario(nodoUsuario* arbolUsuarios)
{
    if (arbolUsuarios == NULL)
    {
        return NULL; // Si el árbol está vacío, retornamos NULL
    }
    nodoUsuario *seg = arbolUsuarios;

    while (seg->der != NULL)
    {
        seg = seg->der;
    }

    return seg;
}


/*nodoUsuario * inicLista()
{
    return NULL;
}

nodoUsuario* buscarMailUsuario(nodoUsuario* listaUsuarios, char * mail)
{
    nodoUsuario * seg = listaUsuarios;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(strcmp(seg->usuario.email, mail) == 0)
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
        return seg;
    }
    else
    {
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

nodoUsuario* buscarUltimoUsuario(nodoUsuario* listaUsuarios)
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
        nodoUsuario * ultimo = buscarUltimoUsuario(listaUsuarios);
        ultimo->sig = nuevo;
    }

    return listaUsuarios;
}

void muestraNodoUsuario(nodoUsuario * nodo)
{
    muestraUnUsuario(nodo->usuario);

}

void muestraListaUsuario(nodoUsuario * listaUsuario)
{
    while(listaUsuario)
    {
        if(listaUsuario->usuario.eliminado == 0)
        {
            muestraNodoUsuario(listaUsuario);
        }
        listaUsuario = listaUsuario->sig;
    }
}

void muestraListaUsuarioBaja(nodoUsuario * listaUsuario)
{
    while(listaUsuario)
    {
        if(listaUsuario->usuario.eliminado == -1){
            muestraNodoUsuario(listaUsuario);
        }
        listaUsuario = listaUsuario->sig;
    }
}

nodoUsuario* buscarIdUsuario(nodoUsuario* listaUsuarios, int idBorrar)
{
    nodoUsuario * seg = listaUsuarios;
    int flag = 0;
    while(seg != NULL && flag == 0)
    {
        if(seg->usuario.idUsuario == idBorrar)
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

nodoUsuario * darDeBajaUsuario(nodoUsuario * listaUsuarios,int idUsuarioActual)
{
    int idBorrar = 0;
    muestraListaUsuario(listaUsuarios);
    printf("\n-----------------------\n");
    printf("Id del usuario a dar de baja");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idBorrar);
    if(idBorrar > idUsuarioActual || idBorrar < 0) ///verifico que la id este entre 0 y las id validas
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeBajaUsuario(listaUsuarios,idUsuarioActual);
    }
    else
    {
        nodoUsuario * userBaja = buscarIdUsuario(listaUsuarios,idBorrar); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(userBaja)
        {
            userBaja->usuario.eliminado = -1;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja usuario.");
        }
    }
    return listaUsuarios;
}

nodoUsuario * darDeAltaUsuario(nodoUsuario * listaUsuarios,int idUsuarioActual)
{
    system("cls");
    int idSubir = 0;
    muestraListaUsuarioBaja(listaUsuarios);
    printf("\n-----------------------\n");
    printf("Id del usuario a dar de alta");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &idSubir);
    if(idSubir > idUsuarioActual || idSubir < 0) ///verifico que la id este entre 0 y las id validas
    {
        printf("\nLa id no existe!\n");
        system("pause");
        darDeAltaUsuario(listaUsuarios,idUsuarioActual);
    }
    else
    {
        nodoUsuario * userAlta = buscarIdUsuario(listaUsuarios,idSubir); ///userBaja va a ser igual al nodo devuelto por buscarIdUsuario (NULL si no esta en la lista)
        if(userAlta)
        {
            userAlta->usuario.eliminado = 0;
        }
        else
        {
            printf("\nOcurrio un error al dar de baja usuario.");
        }
    }
    return listaUsuarios;
}*/

