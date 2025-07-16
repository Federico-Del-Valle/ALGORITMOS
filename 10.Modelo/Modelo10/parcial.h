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
int darBaja(Arbol*, int, FILE *);
int accionMostrar(void *, unsigned , unsigned , void*);
void accionGrabarIndice(void* , unsigned , unsigned , void*);

#endif // PARCIAL_H_INCLUDED
