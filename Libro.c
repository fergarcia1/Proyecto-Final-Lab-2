#include "Libro.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void muestraLibro(stLibro libro)
{
    if(libro.eliminado == 0)
    {
        printf("(Id:%d)", libro.idLibro);
        printf(" %s ", libro.titulo);
        printf("de %s", libro.autor);
        printf("| %s\n", libro.categoria);
    }
}
