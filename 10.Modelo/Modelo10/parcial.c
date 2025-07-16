
#include "arbol.h"
#include "parcial.h"

int cmpIdProd(const void* d, const void* d2)
{
    const indice* ind1 = (const indice*)d;
    const indice* ind2 = (const indice*)d2;
    return ind1->idProducto - ind2->idProducto;
}
int cargarArbol(Arbol* p, char nombre[])
{
    int nroRegistro=0;
    Producto prod;
    indice ind;

    FILE* archProd = fopen(nombre, "rb");
    if(!archProd)
        return 0;
    while(fread(&prod, sizeof(Producto),1,archProd) == 1)
    {
        ind.nroReg = nroRegistro;
        ind.idProducto = prod.idProducto;
        nroRegistro++;
        insertarEnArbol(p,&ind, sizeof(indice),cmpIdProd);
    }
    fclose(archProd);
    return 1;
}

int accionMostrar(void *info, unsigned tamInfo, unsigned nivel, void* params)
{
    const indice* prod = (indice*)info;
    printf("\nLos datos son: \n Idproducto:%-15d \nEstado: %d", prod->idProducto, prod->nroReg);
    return 1;
}

void accionGrabarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params)
{
    FILE* f = (FILE*)params;
    fwrite(info, tamInfo, 1, f);
}

int darBaja(Arbol* p, int idProd, FILE* arch)
{
    Producto prod;
    if(!arch)
        return 0;
    indice ind;
    ind.idProducto = idProd;
    if(buscarElemArbol(p,&ind, sizeof(indice), cmpIdProd) != 1)
    {
        printf("\nEl idProducto no existe");
        return 0;
    }
    printf("ID: %d - Registro: %d\n", ind.idProducto, ind.nroReg);
    rewind(arch);
    fseek(arch,ind.nroReg * sizeof(Producto), SEEK_SET);
    fread(&prod, sizeof(Producto),1, arch);
    prod.estado = 'B';
    fseek(arch, ind.nroReg* sizeof(Producto), SEEK_SET);
    fwrite(&prod,sizeof(Producto),1,arch);

    if(eliminarElem(p,&ind,sizeof(indice),cmpIdProd) != 1)
        return 0;

 return 1;
}



