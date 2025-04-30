#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CLA_DUP -1
#define TODO_OK 1
#define SIN_MEM 2
#define SIN_INICIALIZAR 4
#define ERROR_ARCH 5

#define MINIMO(x, y)((x) <= (y)) ? (x) : (y)

typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* izq;
    struct NodoArbol* der;
}
NodoArbol;

typedef NodoArbol* ArbolBinBusq;

void crearArbolBinBusq(ArbolBinBusq* p);

int insertarArbolBinBusq(ArbolBinBusq* p, const void* d, unsigned tam,
                         int(*cmp)(const void*, const void*));

int insertarRecArbolBinBusq(ArbolBinBusq* p, const void* d, unsigned tam,
                         int(*cmp)(const void*, const void*));

void recorrerEnOrdenArbolBinBusq(const ArbolBinBusq * p, void * params,
                                 void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenInversoArbolBinBusq(const ArbolBinBusq * p, void * params,
                                        void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPreOrdenArbolBinBusq(const ArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPosOrdenArbolBinBusq(const ArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenSimpleArbolBinBusq(const ArbolBinBusq * p,
                                       void * params, void (*accion)(void *, unsigned, void *));

void recorrerPreOrdenSimpleArbolBinBusq(const ArbolBinBusq * p,
                                        void * params, void (*accion)(void *, unsigned, void *));

void recorrerPosOrdenSimpleArbolBinBusq(const ArbolBinBusq * p,
                                        void * params, void (*accion)(void *, unsigned, void *));

int eliminarRaizArbolBinBusq(ArbolBinBusq *p);

int eliminarElemArbolBinBusq(ArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *));

int buscarElemArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                           int (*cmp)(const void *, const void *));

int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(ArbolBinBusq *p, FILE *pf,
                                                unsigned tamInfo);

int cargarArchivoBinOrdenadoArbolBinBusq(ArbolBinBusq *p, const char *path,
                                         unsigned tamInfo);

int cargarDesdeDatosOrdenadosArbolBinBusq(ArbolBinBusq *p,
                                          void *ds, unsigned cantReg,
                                          unsigned (*leer)(void **, void *, unsigned, void *params),
                                          void *params);

int mayorElemNoClaveArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

int menorElemNoClaveArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

int buscarElemNoClaveArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                                  int (*cmp)(const void *, const void *));

/// Utils
unsigned alturaArbolBin(const ArbolBinBusq *p);

unsigned cantNodosArbolBin(const ArbolBinBusq *p);

unsigned cantNodosHastaNivelArbolBin(const ArbolBinBusq *p, int n);

int mayorElemArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam);

int menorElemArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam);

int esCompletoArbolBin(const ArbolBinBusq *p);

int esBalanceadoArbolBin(const ArbolBinBusq *p);

int esAVLArbolBin(const ArbolBinBusq *p);

int esCompleto2ArbolBin(const ArbolBinBusq *p);

int esBalanceado2ArbolBin(const ArbolBinBusq *p);

int esAVL2ArbolBin(const ArbolBinBusq *p);

#endif // ARBOL_H
