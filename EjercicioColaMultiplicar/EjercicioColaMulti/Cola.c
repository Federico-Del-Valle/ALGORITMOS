#include "Cola.h"

void crearCola(Cola* c)
{
    c->pri =NULL;
    c->ult = NULL;
}

int colaLlena(Cola* c, unsigned cantBytes)
{
    int llena;
    Nodo* aux = malloc(sizeof(Nodo));
    void* dato = malloc(cantBytes);
    llena = aux == NULL || dato == NULL;
    free(dato);
    free(aux);
    return llena;
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
    nue->tamDato =tamDato;
    nue->sig = NULL;
    if(c->ult)
    {
        c->ult->sig = nue;
    }
    else
        c->pri = nue;
    c->ult = nue;
    return 1;

}

int verPrimeroCola(Cola* c, void* dato, unsigned tamDato)
{
    if(c->pri == NULL)
        return 0;
    memcpy(dato, c->pri->dato, minimo(tamDato, c->pri->tamDato));
    return 1;
}

int sacarCola(Cola* c, void* dato, unsigned tamDato)
{
    if(c->pri == NULL)
        return 0;
    Nodo* aux = c->pri;
    c->pri = aux->sig;
    memcpy(dato, aux->dato, minimo(tamDato, aux->tamDato));
    free(aux->dato);
    free(aux);
    if(c->pri == NULL)
        c->ult =NULL;
    return 1;
}

int colaVacia(Cola* c)
{
    return c->pri == NULL;
}

void vaciarCola(Cola* c)
{
    while(c->pri)
    {
        Nodo* aux = c->pri;
        c->pri = aux->sig;
        free(aux->dato);
        free(aux);
    }
    c->ult = NULL;
}


