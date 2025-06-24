#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "cliente.h"
#include "Pila.h"

int main()
{

    Arbol arbolClientes;
    crearArbol(&arbolClientes);
    int op;
    Reclamo reclamos[] = {
    {101, 1, "No llega el producto"},
    {102, 1, "Producto defectuoso"},
    {101, 2, "No atienden el telefono"},
    {103, 1, "Demora en entrega"},
    {101, 3, "Mala atención"},
    {101, 4, "Factura errónea"},
    {102, 2, "No reconocen garantía"},
    };
    FILE* archReclamos= fopen("reclamos.dat", "wb");
    if(!archReclamos)
    {
        printf("\nError al abrir reclamos.dat");
        return 0;
    }
    fwrite(reclamos, sizeof(Reclamo), sizeof(reclamos)/ sizeof(Reclamo),archReclamos);

    fclose(archReclamos);

    do
    {
        printf("--MENU--");
        printf("\n1- Procesar archivo reclamos");
        printf("\n2- Recorrer in-order y generar archivo reclamos");
        printf("\n3- Salir");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            procesarArch("reclamos.dat", &arbolClientes);
            break;
        case 2:
            recorrerEnOrdenRecArbolBinBusq(&arbolClientes, 0, NULL, procesarArchTexto);
            break;
        case 3:
            printf("\nADIOS");
        }
    }while(op != 3);

    return 1;
}
