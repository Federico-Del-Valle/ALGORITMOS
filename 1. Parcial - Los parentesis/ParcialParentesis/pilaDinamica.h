#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef *Nodo Pila;

void crearPila(Pila*);
void vaciarPila(Pila*);

int pilaLlena(Pila*);
int pilaVacia(Pila*);


int verTope(Pila*, void*, unsigned);



#endif // PILAESTATICA_H_INCLUDED
