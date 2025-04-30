#ifndef PILA_H
#define PILA_H

#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
}
Nodo;

typedef Nodo* Pila; //Cada vez que declare algo como "Pila" lo voy a declarar como puntero a Nodo

void crearPila(Pila* p);
int pilaLlena(const Pila* p, unsigned cantBytes);
int ponerEnPila(Pila* p, const void* d, unsigned cantBytes);
int verTope(const Pila* p, void* d, unsigned cantBytes);
int pilaVacia(const Pila* p);
int sacarDePila(Pila* p, void* d, unsigned cantBytes);
void vaciarPila(Pila* p);

#endif // PILA_H
