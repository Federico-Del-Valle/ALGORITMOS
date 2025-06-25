#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
}Nodo;
typedef struct
{
    Nodo* pri;
    Nodo* ult;
}Cola;

void crearCola(Cola* p);
int ponerEnCola(Cola* p, void* dato, unsigned tamDato);
int sacarDeCola(Cola* p, void* dato, unsigned tamDato);



#endif // COLA_H_INCLUDED
