#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define minimo(x,y)  (( x ) <= (y) ? (x) : (y) )



typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Pila;

void crearPila(Pila*);
void vaciarPila(Pila*);

int pilaLlena(Pila*);
int pilaVacia( const Pila*);


int verTope(const Pila*, void*, unsigned);
int ponerEnpila(Pila*, void*, unsigned);
int sacarDePila(Pila*, void*, unsigned);



#endif // PILAESTATICA_H_INCLUDED
