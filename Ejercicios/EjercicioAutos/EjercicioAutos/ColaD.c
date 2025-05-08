#include "ColaD.h"

void crearCola(Cola* c)
{
    c->prim = NULL;
    c->ult = NULL;
}

int ponerEnCola(Cola* c, const void* dato, unsigned tamDato)
{
    Nodo* nue = malloc(sizeof(Nodo));
    if(nue == NULL || ((nue->dato = malloc(tamDato)) == NULL))
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato,dato, tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    if(c->prim) // si tiene datos la cola...
        c->ult->sig = nue;
    else
        c->prim = nue;

    c->ult = nue;
    return 1;
}

int sacarDeCola(Cola* c, void* dato, unsigned tamDato)
{
    Nodo* aux = c->prim;
    if(aux == NULL)
        return 0;

    memcpy(dato, aux->dato, minimo(aux->tamDato, tamDato));
    c->prim = aux->sig;
    free(aux->dato);
    free(aux);
    if(c->prim==NULL)
        c->ult = NULL;
    return 1;
}

void vaciarCola(Cola* c)
{
    while(c->prim)
    {
        Nodo* aux = c->prim;
        c->prim = aux->sig;
        free(aux->dato);
        free(aux);
    }
    c->ult = NULL;
}
