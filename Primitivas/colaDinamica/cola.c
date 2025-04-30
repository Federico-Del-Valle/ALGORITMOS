#include "cola.h"

#ifndef minimo
#define minimo(X, Y)    (( (X) <= (Y) ) ? (X) : (Y) )
#endif // minimo

void crearCola(Cola* p)
{
    p->pri = NULL;
    p->ult = NULL;
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
    nue->sig = NULL;
    if(p->ult)
        p->ult->sig = nue;
    else
        p->pri = nue;
    p->ult = nue;
    return 1;
}

int verPrimeroCola(const Cola* p, void* d, unsigned cantBytes)
{
    if(p->pri == NULL)
        return 0;
    memcpy(d, p->pri->info, minimo(cantBytes, p->pri->tamInfo));
    return 1;
}

int colaVacia(const Cola* p)
{
    return p->pri == NULL;
}

int sacarDeCola(Cola* p, void* d, unsigned cantBytes)
{
    Nodo* aux = p->pri;
    if(aux == NULL)
        return 0;

    p->pri = aux->sig;
    memcpy(d, aux->info, minimo(aux->tamInfo, cantBytes));
    free(aux->info);
    free(aux);
    if(p->pri == NULL)
        p->ult = NULL;
    return 1;
}

void vaciarCola(Cola* p)
{
    while(p->pri)
    {
        Nodo* aux = p->pri;
        p->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->ult = NULL;
}


//COLA DINAMICA
