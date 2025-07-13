#ifndef PARCIAL_H_INCLUDED
#define PARCIAL_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    int dni;
    char nombre[];
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
    NodoArbol* izq;
    NodoArbol* der;
}NodoArbol;

typedef NodoArbol* Arbol;

//PUNTO 1

void cargarArbolDesordenado(Arbol* arbolIndice, char[] nombre);
int cmpDni(const void*, const void*);





void iniciarArbol(Arbol*);
int ponerEnArbol(Arbol*, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*));
int eliminarDeArbol(Arbol*, void* dato, unsigned TamDato, int(*cmp)(const void*, const void*));
int buscarEnArbol(Arbol*, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*));


#endif // PARCIAL_H_INCLUDED
