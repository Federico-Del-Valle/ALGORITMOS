#ifndef MAIN_H
#define MAIN_H

//TDA LISTA

#include <stdio.h>

#include "../lineasDeTexto/lineaTexto.h"
#include "../productos/productos.h"
#include "../arbol/arbol.h"

void imprimirConForma(void * info, unsigned tam, unsigned n, void * params);
void imprimir(void * info, unsigned tam, unsigned n, void * params);
unsigned leerDesdeVectorEnteros(void ** d, void * vec, unsigned pos, void * params);
int cmp_ent(const void *v1, const void *v2);

#endif // MAIN_H
