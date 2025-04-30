#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIN_MEM 0
#define TODO_OK 1
#define CLA_DUP 2

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
    struct Nodo* ant;
}
Nodo;

typedef Nodo* Lista;

void crearLista(Lista* p);
int vaciarLista(Lista* p);

int listaLlena(const Lista* p, unsigned cantBytes);
int listaVacia(const Lista* p);

int ponerAlComienzo(Lista* p, const void* d, unsigned cantBytes);
int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes);
int ponerEnOrden(Lista* p, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*),
                 int(*Acumular)(void**, unsigned*, const void*, unsigned));

int mostrarDeIzqADer(const Lista* p, void(*Mostrar)(const void*));
int mostrarDeDerAIzq(const Lista* p, void(*Mostrar)(const void*));

void ordenarLista(Lista* p, int(*Comparar)(const void*, const void*));

int eliminarPorClave(Lista* p, void* d, unsigned cantBytes,
                     int(*Comparar)(const void*, const void*));

#endif // LISTA_H
