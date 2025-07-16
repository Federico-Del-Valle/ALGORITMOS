#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "parcial.h"
int main()
{

    Producto productos[] =
    {
        {13,"Afeitadora",10,'A'},
        {1,"Podadora",10,'A'},
        {4,"Chicles",16,'A'},
        {20,"Cafe",15,'A'},
        {30,"Remera",11,'A'},
        {22,"Sarten",10,'A'},
        {21,"Coca-cola",30,'A'},
        {2,"Lima",1,'A'}
    };
    FILE* archProd = fopen("productos.dat", "wb");
    if(!archProd)
    {
        printf("\nError");
        return 0;
    }

    fwrite(productos,sizeof(Producto), sizeof(productos)/sizeof(Producto), archProd);
    fclose(archProd);
    Arbol arbolIdx;
    iniciarArbol(&arbolIdx);
    FILE* arch = fopen("productos.dat", "rb+");

    int op;
    int prod;

    printf("\nMENU");
    do
    {
        printf("\nSeleccione una opcion:");
        printf("\n1- Cargar arbol");
        printf("\n2- Dar baja producto");
        printf("\n3- Ver si es completo");
        printf("\n4- Ver si es AVL");
        printf("\n5- Mostrar arbol");
        printf("\n6- Salir");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cargarArbol(&arbolIdx, "productos.dat");
            break;

        case 2:
            printf("\nQue producto desea dar de baja?");
            scanf("%d", &prod);
            darBaja(&arbolIdx,prod,arch);
            break;

        case 3:
            if(esCompleto(&arbolIdx))
                printf("\nEs completo");
            else
                printf("\nNo es completo");
            break;
        case 4:
            if(esAVL(&arbolIdx))
                printf("\nEs AVL");
            else
                printf("\nNo es AVL");
            break;
        case 5:
            recorrerArbol(&arbolIdx,0,NULL,accionMostrar);
            FILE* archivoIdx = fopen("productos.idx", "wb");
            if(!archivoIdx)
                return 0;
            recorrerArbol(&arbolIdx,0,archivoIdx, accionGrabarIndice);
            fclose(archivoIdx);
            break;
        case 6:
            fclose(arch);
            printf("\nadios");
            break;

        }
    }while(op != 6);




    return 0;
}
