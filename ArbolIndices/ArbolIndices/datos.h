#ifndef DATOS_H_INCLUDED
#define DATOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/** === Definiciones generales === **/
typedef struct {
    int clave;
    char nombre[30];
} Registro;

/** === Nodo del árbol binario de búsqueda === **/
typedef struct sNodoArbol {
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq, *der;
} tNodoArbol;
typedef tNodoArbol *tArbolBinBusq;

/** === Estructura para el índice === **/
typedef struct {
    int clave;
    unsigned offset;
} tIndice;







#endif // DATOS_H_INCLUDED
