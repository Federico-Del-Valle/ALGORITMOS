#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED
#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#define minimo(x,y) (x) < (y) ? (x) : (y)

typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Pila;

void crearPila(Pila*);
void vaciarPila(Pila*);

int ponerEnPila(Pila*, void*, unsigned);
int sacarDePila(Pila*, void*, unsigned);

int verTope(const Pila*, void*, unsigned);

int pilaVacia(Pila*);



#endif // PILADINAMICA_H_INCLUDED
