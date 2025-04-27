#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define minimo(x,y) ((x) < (y) ? (x) : (y))


#define URL_MAX 100

typedef struct {
    char url[URL_MAX];
} Pagina;

typedef struct sNodo {
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
} tNodo;

typedef tNodo* tPila;

// ==== PRIMITIVAS A IMPLEMENTAR (usar las que hice anteriormente) ====
// ==== esto va en un archivo .h ====
void crearPila(tPila *p);
int apilar(tPila *p, const void *dato, unsigned tamDato);
int desapilar(tPila *p, void *dato, unsigned tamDato);
int verTope(const tPila *p, void *dato, unsigned tamDato);
int pilaVacia(const tPila *p);
void vaciarPila(tPila *p);

#endif // PILA_H_INCLUDED
