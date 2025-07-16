#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED


typedef struct NodoLista
{
    void* info;
    unsigned tamInfo;
    struct NodoLista* sig;
}NodoLista;

typedef NodoLista* Lista;

#endif // LISTA_H_INCLUDED
