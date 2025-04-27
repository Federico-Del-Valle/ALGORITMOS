#include "Pila.h"

void crearPila(tPila* p)
{
    *p= NULL;
}

int apilar(tPila *p, const void *dato, unsigned tamDato)
{
    tNodo* nue = malloc(sizeof(tNodo));
    if(nue== NULL || ((nue->dato=malloc(tamDato)) == NULL))
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato= tamDato;
    nue->sig= *p;
    *p = nue;

    return 1;
}

int desapilar(tPila *p, void *dato, unsigned tamDato)
{
    if(!*p)
        return 0;

    tNodo* aux = *p;

    memcpy(dato, aux->dato, minimo(aux->tamDato, tamDato));
    *p = aux->sig;
    free(aux->dato);
    free(aux);
    return 1;
}

int verTope(const tPila *p, void* dato, unsigned tamDato)
{
    if(!*p)
        return 0;
    memcpy(dato, (*p)->dato, minimo(tamDato,(*p)->tamDato));
    return 1;
}
void vaciarPila(tPila *p)
{
    tNodo* aux;
    while(*p)
    {
        aux = *p;
        *p = aux->sig;
        free(aux->dato);
        free(aux);
    }
}

