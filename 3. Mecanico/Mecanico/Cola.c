
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Cola.h"


void iniciarCola(Cola* p)
{
    p->pri = NULL;
    p->ult = NULL;
}

void vaciarCola(Cola* p)
{
    while(p->pri)
    {
        Nodo* aux = p->pri; //apunta al primero de la cola
        p->pri = aux->sig;
        free(aux->dato);
        free(aux);
    }
    p->ult=NULL;
}

int ponerEnCola(Cola* p, void* dato, unsigned tamDato)
{
    Nodo* nue;
    if((nue = malloc(sizeof(Nodo))) == NULL || (nue->dato = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->sig=NULL;
    nue->tamDato= tamDato;

    if(p->pri == NULL)
    {
        p->pri = nue;
        p->ult = nue;
    }
    else
    {
        p->ult->sig = nue;
        p->ult = nue;
    }
    return 1;
}
