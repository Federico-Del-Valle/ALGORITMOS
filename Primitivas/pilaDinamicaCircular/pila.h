#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

//Pila dinamica circular

#include <string.h>
#include <stdlib.h>

#define minimo(x, y) ((x <= y) ? (x) : (y))

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
}
Nodo;

typedef Nodo* Pila;

void crearPila(Pila* p);
void vaciarPila(Pila* p);

int pilaLlena(const Pila* p, unsigned cantBytes);
int pilaVacia(const Pila* p);

int ponerEnPila(Pila* p, const void* d, unsigned cantBytes);
int sacarDePila(Pila* p, void* d, unsigned cantBytes);

int verTope(const Pila* p, void* d, unsigned cantBytes);

#endif // PILA_H_INCLUDED
