#include "pilaDinamica.h"

void crearPila(Pila* p)
{
    *p= NULL;
}

int pilaVacia(const Pila* p)
{
    return *p == NULL;
}

void vaciarPila(Pila* p)
{
    while(*p)
    {
        Nodo* aux = *p;
        *p = aux->sig;
        free(aux->dato);
        free(aux);

    }
}

int ponerEnpila(Pila* p, void* dato, unsigned tamDato)
{
    Nodo* nue;
    if( (nue = malloc(sizeof(Nodo)))== NULL || (nue->dato = malloc(tamDato)) == NULL )
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->sig = *p;
    *p = nue;
    return 1;
}

int sacarDePila(Pila* p, void* dato,unsigned tamDato)
{
    if(*p == NULL)
    return 0;

    Nodo* aux = *p;

    memcpy(dato, aux->dato, minimo(tamDato, aux->tamDato));
    *p= aux->sig;
    free(aux->dato);
    free(aux);
    return 1;

}

int verTope(const Pila* p, void* dato, unsigned tamDato)
{
    if(*p ==NULL)
    {
        return 0;
    }
    memcpy(dato, (*p)->dato, minimo(tamDato, (*p)->tamDato));
    return 1;
}


