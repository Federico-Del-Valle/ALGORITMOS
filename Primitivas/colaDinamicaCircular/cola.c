#include "cola.h"

#ifndef minimo
#define minimo(X, Y)    (( (X) <= (Y) ) ? (X) : (Y) )
#endif // minimo

void crearCola(Cola* p)
{
    *p = NULL;
}

int colaLlena(const Cola* p, unsigned cantBytes)
{
    Nodo* aux = malloc(sizeof(Nodo));
    void* info = malloc(cantBytes);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ponerEnCola(Cola *p, const void *d, unsigned cantBytes)
{
    Nodo* nue = malloc(sizeof(Nodo));

    if(nue == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;

    if(*p == NULL)
        nue->sig = nue;
    else
    {
        nue->sig = (*p)->sig;
        (*p)->sig = nue;
    }

    *p = nue;
    return 1;
}

int verPrimeroCola(const Cola* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->sig->info, minimo(cantBytes, (*p)->sig->tamInfo));
    return 1;
}

int colaVacia(const Cola* p)
{
    return *p == NULL;
}

int sacarDeCola(Cola* p, void* d, unsigned cantBytes)
{
    Nodo* aux;

    if(*p == NULL)
        return 0;

    aux = (*p)->sig;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));

    if(aux == *p)
        *p = NULL;
    else
        (*p)->sig = aux->sig;

    free(aux->info);
    free(aux);

    return 1;
}

void vaciarCola(Cola* p)
{
    while(*p)
    {
        Nodo* aux = (*p)->sig;

        if(*p == aux)
            *p = NULL;
        else
            (*p)->sig = aux->sig;

        free(aux->info);
        free(aux);
    }
}


//COLA DINAMICA
