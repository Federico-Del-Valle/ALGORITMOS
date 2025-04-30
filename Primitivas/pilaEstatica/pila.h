#ifndef PILA_H
#define PILA_H

#include <string.h>

#define TAM_PILA 900

typedef struct
{
    char pila[TAM_PILA];
    unsigned tope;
}
Pila;

void crearPila(Pila* p);
void vaciarPila(Pila* p);

int pilaLlena(const Pila* p, unsigned cantBytes);
int pilaVacia(const Pila* p);

int verTope(const Pila* p, void* d, unsigned cantBytes);

int ponerEnPila(Pila* p, const void* d, unsigned cantBytes);
int sacarDePila(Pila* p, void* d, unsigned cantBytes);


#endif // PILA_H
