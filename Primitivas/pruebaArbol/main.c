#include "main.h"

//TDA ARBOL

int main()
{
    ArbolBinBusq arr;
    int vec[] = {10,25,50,60,75,100,115,125,150,175,200};
    int dato;

    crearArbolBinBusq(&arr);
    cargarDesdeDatosOrdenadosArbolBinBusq(&arr, vec, sizeof(vec)/sizeof(int),
                                          leerDesdeVectorEnteros,NULL);
    //eliminarRaizArbolBinBusq(&arr);

    recorrerEnOrdenArbolBinBusq(&arr,NULL,imprimir);
    printf("\n\n");
    recorrerPreOrdenArbolBinBusq(&arr,NULL,imprimir);
    printf("\n\n");
    recorrerPosOrdenArbolBinBusq(&arr,NULL,imprimir);
    printf("\n\n");
    recorrerEnOrdenInversoArbolBinBusq(&arr,NULL,imprimirConForma);

    printf("\n\n");
    if (esCompletoArbolBin(&arr))
        printf("\nCompleto");
    if (esBalanceadoArbolBin(&arr))
        printf("\nBalanceado");
    if(esAVLArbolBin(&arr))
        printf("\nAVL");

    printf("\n\n");
    if (esCompleto2ArbolBin(&arr))
        printf("\n2 Completo");
    if (esBalanceado2ArbolBin(&arr))
        printf("\n2 Balanceado");
    if(esAVL2ArbolBin(&arr))
        printf("\n2 AVL");

    mayorElemNoClaveArbolBinBusq(&arr, &dato, sizeof(dato),cmp_ent);
    printf("\nMayor No Clave: %d", dato);

    menorElemNoClaveArbolBinBusq(&arr, &dato, sizeof(dato),cmp_ent);
    printf("\nMenor No Clave: %d", dato);

    return 0;
}

void imprimirConForma(void * info, unsigned tam, unsigned n, void * params)
{
    int * i = (int *) info;
    printf("%*s-%3d-\n", n*3, "", *i);
}

void imprimir(void * info, unsigned tam, unsigned n, void * params)
{
    int * i = (int *) info;
    printf("-%d-", *i);
}

unsigned leerDesdeVectorEnteros(void ** d, void * vec, unsigned pos, void * params)
{
    *d = malloc(sizeof(int));
    if(!*d)
        return 0;
    memcpy(*d, vec+(sizeof(int)*pos), sizeof(int));
    return sizeof(int);
}

int cmp_ent(const void *v1, const void *v2)
{
    return *(int*)v1 - *(int*)v2;
}
