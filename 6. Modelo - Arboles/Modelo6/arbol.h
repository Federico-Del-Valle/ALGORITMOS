#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* izq;
    struct NodoArbol* der;
}NodoArbol;

typedef NodoArbol* Arbol;

void crearArbol(Arbol* p);
void vaciarArbol(Arbol* p);

int ponerEnArbolRec(Arbol* p, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*), int(*acumular)(void*, void*));




#endif // ARBOL_H_INCLUDED
