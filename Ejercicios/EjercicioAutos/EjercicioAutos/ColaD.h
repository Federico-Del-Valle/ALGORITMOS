#ifndef COLAD_H_INCLUDED
#define COLAD_H_INCLUDED
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define minimo(x,y) ((x) < (y) ? (x) : (y))
typedef struct {
    char patente[10];
    char tipo[20];
    int tiempo; // en minutos
} Vehiculo;

typedef struct sNodo {
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
} Nodo;

typedef struct {
    Nodo *prim;
    Nodo *ult;
} Cola;

void crearCola(Cola *c);
int ponerEnCola(Cola *c, const void *dato, unsigned tamDato);
int sacarDeCola(Cola *c, void *dato, unsigned tamDato);
int verFrente(const Cola *c, void *dato, unsigned tamDato);
int colaVacia(const Cola *c);
void vaciarCola(Cola *c);

#endif // COLAD_H_INCLUDED
