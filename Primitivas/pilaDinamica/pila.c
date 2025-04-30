#include "pila.h"

#ifndef minimo //para no redefinir en caso de que ya este definida la macro
#define minimo(x, y)((x) <= (y) ? (x) : (y))
#endif // minimo

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

    if((nuevo = malloc(sizeof(Nodo))) == NULL || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *p;
    *p = nuevo;

    return 1;
}

int sacarDePila(Pila* p, void* d, unsigned cantBytes)
{
    Nodo* aux = *p;

    if(aux == NULL)
        return 0;

    *p = aux->sig;

    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);

    return 1;
}

int verTope(const Pila* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}


