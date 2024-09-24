#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#definde TAM_PILA 340


typedef struct
{
    char pila[TAM_PILA];
    unsigned tope;
}tPila;

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tPila;


#endif // PILA_H_INCLUDED
