#ifndef COLA_H
#define COLA_H

//COLA DINAMICA

#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
}
Nodo;

typedef Nodo* Cola;

void crearCola(Cola *p);
void vaciarCola(Cola *p);

int colaLlena(const Cola *p, unsigned cantBytes);
int colaVacia(const Cola *p);

int ponerEnCola(Cola *p, const void *d, unsigned cantBytes);
int sacarDeCola(Cola *p, void *d, unsigned cantBytes);

int verPrimeroCola(const Cola *p, void *d, unsigned cantBytes);

#endif // COLA_H
