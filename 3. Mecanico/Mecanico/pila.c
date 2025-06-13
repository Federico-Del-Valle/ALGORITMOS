#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"


void crearPila(Pila* p)
{
    *p = NULL;
}

int pilaVacia(const Pila* p)
{
    return *p == NULL;
}

void vaciarPila(Pila* p)
{
    while(*p)
    {
        Nodo* aux = *p;
        *p = aux->sig;
        free(aux->dato);
        free(aux);
    }
}

int ponerEnPila(Pila* p, void* dato, unsigned tamDato)
{
    Nodo* nuevo;
    if((nuevo = malloc(sizeof(Nodo)))== NULL || (nuevo->dato = malloc(sizeof(tamDato))) == NULL)
    {
        free(nuevo);
        return 0;
    }
    memcpy(nuevo->dato, dato, tamDato);
    nuevo->tamDato = tamDato;
    nuevo->sig = *p;
    *p = nuevo;

    return 1;
}

int sacarDePila(Pila* p, void* dato, unsigned tamDato)
{
    if(*p == NULL)
    {
        return 0;
    }
    Nodo* aux = *p;
    memcpy(dato, aux->dato, minimo(tamDato, aux->tamDato));
    *p = aux->sig;
    free(aux->dato);
    free(aux);
    return 1;
}


