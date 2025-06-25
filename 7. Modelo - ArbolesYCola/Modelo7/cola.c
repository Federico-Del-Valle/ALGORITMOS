#include "cola.h"
#define minimo(x,y) ((x) < (y) ? (x):(y) )



void crearCola(Cola* p)
{
    p->pri = NULL;
    p->ult = NULL;
}

int ponerEnCola(Cola* p, void* dato, unsigned tamDato)
{
    Nodo* nue;
    if((nue = malloc(sizeof(Nodo))) == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = NULL;
    if(p->ult)
    {
        p->ult->sig = nue;
        p = nue;
    }
    else
    {
        p->pri = nue;
    }
    p->ult = nue;
    return 1;
}
int sacarDeCola(Cola* p, void* dato, unsigned tamDato)
{
    Nodo* aux = p->pri;

    if(aux == NULL)
        return 0;
    memcpy(dato, aux->info,minimo(aux->tamInfo,tamDato));
    p->pri = aux->sig;
    free(aux->info);
    free(aux);
    if(p->pri ==NULL)
        p->ult=NULL;
    return 1;
}
