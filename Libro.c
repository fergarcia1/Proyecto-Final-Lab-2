#include "Libro.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void muestraLibro(stLibro libro)
{
        printf("(Id:%d)", libro.idLibro);
        printf(" %s ", libro.titulo);
        printf("de %s", libro.autor);
        printf("| %s ", libro.categoria);
        printf("| %f |\n\n", libro.valoracion);
}

stLibro modificarLibros(stLibro libro/*,nodoLibro * listaLibro*/)
{
    system("cls");
    stLibro libroAux = libro;
    int valor = 0;
    printf("\n-----------------------\n");
    printf("1. Modificar Titulo.");
    printf("\n-----------------------\n");
    printf("2. Modificar Editorial.");
    printf("\n-----------------------\n");
    printf("3. Modificar Autor.");
    printf("\n-----------------------\n");
    printf("4. Modificar Categoria.");
    printf("\n-----------------------\n");
    printf("5. Modificar Valoracion.");
    printf("\n-----------------------\n");
    printf("6. Volver al menu.");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%d",&valor);
    switch(valor)
    {
    case(1):
        printf("Nuevo titulo de libro: \n");
        fflush(stdin);
        gets(libroAux.titulo);
        printf("Titulo del libro modificado correctamente. \n");
        system("pause");
        return libroAux;
        break;
    case(2):
        printf("Nueva editorial de libro: \n");
        fflush(stdin);
        gets(libroAux.editorial);
        printf("Editorial del libro modificada correctamente. \n");
        system("pause");
        return libroAux;
        break;
    case(3):
        printf("Nuevo autor del libro: \n");
        fflush(stdin);
        gets(libroAux.autor);
        system("pause");
        return libroAux;
        break;
    case(4):
        printf("Nueva categoria de libro: \n");
        fflush(stdin);
        gets(libroAux.categoria);
        printf("Categoria del libro modificada correctamente.");
        system("pause");
        return libroAux;
        break;
    case(5):
        printf("Nueva valoracion de libro: \n");
        fflush(stdin);
        scanf("%f",&libroAux.valoracion);
        printf("Valoracion del libro modificada correctamente. \n");
        system("pause");
        return libroAux;
        break;
    case(6):
        return libroAux;
        break;
    }
    return libroAux;
}
