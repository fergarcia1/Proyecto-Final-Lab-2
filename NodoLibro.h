#ifndef NODOLIBRO_H_INCLUDED
#define NODOLIBRO_H_INCLUDED

#include "Libro.h"
#include <conio.h>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    stLibro libro;
    struct nodoLibro* sig;
}nodoLibro;

nodoLibro * crearNodoLibro(stLibro libro);
nodoLibro * agregarAlFinalLibro(nodoLibro * listaLibro, nodoLibro * nuevo);


#endif // NODOLIBRO_H_INCLUDED
