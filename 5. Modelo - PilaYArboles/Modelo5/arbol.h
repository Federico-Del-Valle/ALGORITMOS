#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* izq;
    struct NodoArbol* der;
}NodoArbol;

typedef NodoArbol* Arbol;

void crearArbol(Arbol* a);

int insertarArbol(Arbol* p, void* dato, unsigned tamDato,
                  int(*comparar)(const void*, const void*),
                  int(*acumular)(void*, const void*));

void recorrerEnOrdenRecArbolBinBusq(const Arbol * p, unsigned n, void * params, void (*accion)(void *, unsigned, unsigned, void *));


#endif // ARBOL_H_INCLUDED
