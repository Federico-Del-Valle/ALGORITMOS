#ifndef COLA_H
#define COLA_H

//COLA ESTATICA

#include <string.h>
#include <stdlib.h>

#define TAM_COLA 1000

typedef struct
{
    char cola[TAM_COLA];
    unsigned    pri,
                ult,
                tamDisp;
}
Cola;

void crearCola(Cola* p);
void vaciarCola(Cola* p);

int colaLlena(const Cola* p, unsigned cantBytes);
int colaVacia(const Cola* p);

int ponerEnCola(Cola* p, const void* d, unsigned cantBytes);
int sacarDeCola(Cola* p, void* d, unsigned cantBytes);

int verPrimeroCola(const Cola* p, void* d, unsigned cantBytes);

#endif // COLA_H
