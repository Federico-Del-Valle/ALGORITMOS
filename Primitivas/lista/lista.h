#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIN_MEM  1
#define CLA_DUP  2
#define TODO_OK  0

typedef struct Nodo
{
    void *info;
    unsigned tamInfo;
    struct Nodo* sig;
}
Nodo;

typedef Nodo* Lista;

void crearLista(Lista* p);
//void vaciarLista(Lista* p);
int vaciarLista(Lista* p);
int vaciarListaYMostrar(Lista* p, void (*Mostrar)(const void*, FILE*), FILE* fp);

int listaLlena(const Lista* p, unsigned cantBytes);
int listaVacia(const Lista* p);

int ponerAlComienzo(Lista* p, const void* d, unsigned cantBytes);
int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes);
int ponerEnOrden(Lista* lista, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*),
                 int(*Acumular)(void**, unsigned*, const void*, unsigned));

int sacarPrimeroLista(Lista* p, void* d, unsigned cantBytes);
int sacarUltimoLista(Lista* p, void* d, unsigned cantBytes);

int verPrimeroLista(const Lista* p, void* d, unsigned cantBytes);
int verUltimoLista(const Lista* p, void* d, unsigned cantBytes);

int mostrarLista(Lista* p, void (*Mostrar)(const void*, FILE*), FILE* fp);
int mostrarListaAlReves(Lista* p, void (*Mostrar)(const void*, FILE*), FILE* fp); //Recursiva
int mostrarListaAlRevesYVaciar(Lista* p, void (*Mostrar)(const void*, FILE*), FILE* fp);

void ordenarLista(Lista* p, int(*Comparar)(const void*, const void*));

#endif // LISTA_H
