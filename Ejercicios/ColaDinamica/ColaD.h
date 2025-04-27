#ifndef COLAD_H_INCLUDED
#define COLAD_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define minimo(x,y) ((x) < (y) ? (x) : (y))
typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef struct
{
    Nodo* pri;
    Nodo* ult;
}Cola;
void crearCola(Cola*);
int colaLlena(Cola*, unsigned);
int ponerEnCola(Cola* , const void*, unsigned);
int sacarCola(Cola*, void*, unsigned);
void vaciarCola(Cola*);
int verPrimeroCola(Cola*, void*, unsigned);
int colaVacia(Cola*);

#endif // COLAD_H_INCLUDED
