#include "pilaDinamica.h"

void crearPila(Pila* p)
{
    *p = NULL;
}

int pilaVacia(Pila* p)
{
    return *p == NULL;
}

int ponerEnPila(Pila* p, void* d, unsigned tam)
{
    Nodo* nuevo;

    if((nuevo = malloc(sizeof(Nodo)))== NULL || (nuevo->dato = malloc(tam)) == NULL)
    {
        free(nuevo);
        return 0;
    }
    memcpy(nuevo->dato, d, tam);
    nuevo->tamDato = tam;
    nuevo->sig = *p;
    *p = nuevo;
    return 1;
}


int sacarDePila(Pila* p, void* dato, unsigned tam)
{
    if(*p == NULL)
        return 0;
    Nodo* aux = *p;
    memcpy(dato, aux->dato, minimo(tam, aux->tamDato));
    (*p) = aux->sig;
    free(aux->dato);
    free(aux);


    return 1;
}


int verTope(const Pila* p, void* dato, unsigned tam)
{
    if((*p) == NULL)
    {
        printf("Pila vacia");
        return 0;
    }
    memcpy(dato, (*p)->dato, minimo(tam, (*p)->tamDato));
    return 1;
}


