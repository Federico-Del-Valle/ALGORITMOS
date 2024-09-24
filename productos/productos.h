#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char codProd[11];
    char descrip[46];
}tprod;

int ingresarProd(tprod *d);

void mostrarProd(const tprod *d);

#endif // PRODUCTOS_H_INCLUDED
