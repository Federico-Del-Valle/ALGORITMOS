#include "pila.h"
#include <stdio.h>

void crearPila(Pila* p)
{
    *p = NULL;
}

void vaciarPila(Pila* p)
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

int pilaLlena(const Pila* p, unsigned cantBytes)
{
    Nodo* aux = malloc(sizeof(Nodo));
    void* info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int pilaVacia(const Pila* p)
{
    return *p == NULL;
}

int ponerEnPila(Pila* p, const void* d, unsigned cantBytes)
{
    Nodo* nuevo;
    //Nodo* nuevoMio;
    //Nodo* nuevoMioSig;

    if((nuevo = malloc(sizeof(Nodo))) == NULL ||
       (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    //nuevoMio = nuevo; //MIO

    if(*p == NULL)
    {
        nuevo->sig = nuevo;
        //nuevoMioSig = nuevo->sig;
        *p = nuevo;
    }
    else
    {
        nuevo->sig = (*p)->sig;
        (*p)->sig = nuevo;
        //nuevoMioSig = nuevo->sig;
    }

    //printf("t:%p, p-sig:%p \nnuevo:%p nuevo-sig:%p  \n", *p, (*p)->sig, nuevoMio, nuevoMioSig);
    return 1;
}

int sacarDePila(Pila* p, void* d, unsigned cantBytes)
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

    //printf(" Tope: %p, p->sig: %p \n", *p, (*p)->sig);

    free(aux->info);
    free(aux);

    return 1;
}

int verTope(const Pila* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->sig->info, minimo(cantBytes, (*p)->sig->tamInfo));
    return 1;
}
