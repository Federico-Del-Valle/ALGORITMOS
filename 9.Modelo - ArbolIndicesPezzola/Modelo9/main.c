#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"


int main()
{

    Arbol arbolIndice;
    crearArbol(&arbolIndice);
    cargarArbolDesordenado(&arbolIndice, "alumnos.dat");
    int op;
    printf("Parcial\n");

    do
    {
        printf("---MENU---\n");
        printf("\n1- Dar de baja alumno");
        printf("\n2- Armar arbol de indices");
        printf("\n3- Vaciar arbol");
        printf("\n4-Cerrar el programa");
        printf("Seleccione una opcion");
        scanf("%d", &op);
    }while(op != 4);

    return 0;
}
