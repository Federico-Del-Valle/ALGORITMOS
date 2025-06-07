#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "pasajero.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Lista;


#endif // LISTA_H_INCLUDED
