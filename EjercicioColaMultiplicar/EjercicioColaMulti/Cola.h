#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y) (((x) > (y)) ? (x) : (y) )

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
int ponerEnCola(Cola*, const void*, unsigned);
int verPrimeroCola(Cola*, void*, unsigned);
int sacarCola(Cola*, void*, unsigned);
int colaVacia(Cola*);
void vaciarCola(Cola*);

#endif // COLA_H_INCLUDED
