#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdlib.h>
#include <string.h>

typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* der;
    struct NodoArbol* izq;
}NodoArbol;

typedef NodoArbol* Arbol;


void crearArbol( Arbol* p);
int ponerEnArbol(Arbol* p, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*), int (*accion)(void*, unsigned, void*));
int eliminarPorDni(Arbol* p, int dni, void* dato, unsigned tamElim);
void recorrerArbol(Arbol* p, unsigned n, int(*accion)(void* , unsigned n, void*));
int compararPorDni(const void*, const void*);
int mostrarPersona(void* dato, unsigned tamDato, void* param);
int alturaArbol(const Arbol* p);
#endif // ARBOL_H_INCLUDED
