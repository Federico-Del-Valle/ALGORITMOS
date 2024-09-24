#include "productos.h"

int ingresarProd(tprod *d)
{
    static const tprod productos[] = {
    {"clavoro", "Clavo de oro 25 kilates"},
    {"martillo", "martillo para matar gigantes"},
    {"Guante", "guante para jugar a ser Thanos"}
        };
    static int posi = 0;

    if(posi == sizeof(productos) / sizeof(tprod))
    {
        posi = 0;
        return 0;
    }
    *d = productos[posi];
    posi++;
    return 1;
}


void mostrarProd(const tprod *d)
{
    if (d)
        // Imprimir el producto
        printf("%-20s %-30s\n", d->codProd ,d->descrip);

}
