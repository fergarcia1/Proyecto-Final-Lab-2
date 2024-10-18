#include "Libro.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void muestraLibro(stLibro libro)
{
        printf("(Id:%d)", libro.idLibro);
        printf(" %s ", libro.titulo);
        printf("de %s", libro.autor);
        printf("| %s\n", libro.categoria);
}
