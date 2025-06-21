#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "lote.h"

typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Lista;

void crearLista(Lista* p);
void vaciarLista(Lista* p);

int ponerAlIni(Lista* p, void* dato, unsigned tamDato);
int ponerAlFinal(Lista* p, void* dato, unsigned tamDato);
int sacarDeLista(Lista* p, void* dato, unsigned tamDato);

int OrdenarLista(Lista* p, int(*Comparar)(const void*, const void*));

int insertarOrdenado(Lista* p, void* dato, unsigned tamDato, int(*Comparar)(const void*, const void*),
                     int(*Acumular)(const void*, const void*));


#endif // LISTA_H_INCLUDED
