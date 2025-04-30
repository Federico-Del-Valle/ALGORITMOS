#include "productos.h"

int ingresarProducto(Producto* d)
{
    Producto productos[] =
    {
        {"clavooro", "Clavo de oro 24 kilates"},
        {"martillo3K", "Martillo bolita con saca clavos"},
        {"alamyeso1", "Alambre de yeso un milimetro"},
        {"red-vid15", "Remached de vidrio de 1,5 milimetros"},
        {"plom-telgo", "Plomada de poliestireno expandido"},
        {"limagoma17", "Lima de goma de 17 pulgadas"}
    };

    static int posIni = 0;
    //sin el static no funciona

    if(posIni == sizeof(productos)/sizeof(Producto))
    {
        posIni = 0;
        return 0;
    }

    *d = productos[posIni];
    posIni++;

    return 1;
}

void mostrarProductoTxt(const Producto* d, FILE* fp)
{
    if(d)
        fprintf(fp,
                "%-*s %-*s ...\n",
                (int) sizeof(d->codProd) - 1, d->codProd,
                (int) sizeof(d->descrip) - 1, d->descrip);
    else
        fprintf(fp,
                "%-*.*s %-*.*s ...\n",
                (int) sizeof(d->codProd) - 1, (int) sizeof(d->codProd) - 1, "Cod. Producto",
                (int) sizeof(d->descrip) - 1, (int) sizeof(d->descrip) - 1, "Descripcion del producto");
}

void mostrarProducto(const Producto* d)
{
    mostrarProductoTxt(d, stdout);
}

void mostrarProductoTxtTDA(const void* d, FILE* fp)
{
    mostrarProductoTxt((const Producto*) d, fp);
}

void grabarProductoBinTDA(const void* d, FILE* fp)
{
    fwrite(d, sizeof(Producto), 1, fp);
}
