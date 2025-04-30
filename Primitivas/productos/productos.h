#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <stdio.h>

typedef struct
{
    char    codProd[11],
            descrip[46];
}
Producto;

int ingresarProducto(Producto* d);
void mostrarProductoTxt(const Producto* d, FILE* fp);

void mostrarProducto(const Producto* d);
void mostrarProductoTxtTDA(const void* d, FILE* fp);
void grabarProductoBinTDA(const void* d, FILE* fp);

#endif // PRODUCTOS_H
