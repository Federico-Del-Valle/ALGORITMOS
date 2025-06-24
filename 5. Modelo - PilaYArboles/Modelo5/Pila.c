#include "Pila.h"
#include "cliente.h"

#define minimo(x,y) ((x) <= (y) ? (x) : (y) )

void crearPila(Pila* p)
{
    *p = NULL;
}

void vaciarPila(Pila* p)
{
    while(*p)
    {
        Nodo* aux = *p;
        *p = aux->sig;

        free(aux->info);
        free(aux);
    }
}

int ponerEnPila(Pila* p, void* dato, unsigned tamDato)
{
    Nodo* nue;
    if((nue = malloc(sizeof(Nodo))) == NULL || (nue->info = malloc(tamDato))== NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = *p;
    *p = nue;

    return 1;
}

int sacarDePila(Pila* p, void* dato, unsigned tamDato)
{
    if(*p == NULL)
    {
        return 0;
    }
    Nodo* aux = *p;
    memcpy(dato, aux->info, minimo(tamDato, aux->tamInfo));
    *p = aux->sig;
    free (aux->info);
    free(aux);
    return 1;
}
