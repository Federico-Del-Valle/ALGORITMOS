#ifndef PARCIAL_H_INCLUDED
#define PARCIAL_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arbol.h"

typedef struct
{
    int idProducto;
    char descripcion[50];
    int stock;
    char estado;
}Producto;

int cargarArbol(Arbol* , char[]);
int darBaja(Arbol*, int, char[]);



#endif // PARCIAL_H_INCLUDED
