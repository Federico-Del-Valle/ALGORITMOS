#ifndef PARCIAL_H_INCLUDED
#define PARCIAL_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    int dni;
    char nombre[20];
    char estado;
}Alumno;

typedef struct
{
    int indice;
    int dni;
}Indice;

typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* izq;
    struct NodoArbol* der;
}NodoArbol;

typedef NodoArbol* Arbol;

//PUNTO 1

void crearArbol(Arbol* arbol);
int insertarEnArbol(Arbol* p, void* d, unsigned tamDato, int(*cmp)(const void*, const void*));
NodoArbol** buscarNodo(const Arbol* p, const void* d, int(*cmp)(const void*, const void*));
int buscarEnArbol(Arbol* p, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*));
int darDeBaja(Arbol* p, int dni, char nombre[]);
void accionGrabarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params);
void cargarArbolDesordenado(Arbol* arbolIndice, char nombre[]);
int cmpDni(const void* dato1, const void* dato2);
void recorrerEnOrdenRecArbolBinBusq(const Arbol* p, unsigned n, void* params,void (*accion)(void*, unsigned, unsigned, void*));
void accionMostrarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params);

#endif // PARCIAL_H_INCLUDED
