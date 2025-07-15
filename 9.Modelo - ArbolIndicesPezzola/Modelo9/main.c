#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"


int main()
{

    Alumno alumnos[] =
    {
        {443316258,"Federico Del Valle",'A'},
        {424555444,"Hernest",'B'},
        {345848333,"Mariana Del Valle",'A'},
        {256848484,"Juani ota",'A'},
        {356828222,"Lucas galle",'A'},
        {400000000,"Delfina Garcia Molina",'A'},
        {543333333,"Juan Manuel",'A'},
        {523444444,"Marito barakus",'A'}};

    FILE* arch = fopen("alumnos.dat", "wb");
    fwrite(alumnos,sizeof(Alumno), sizeof(alumnos)/sizeof(Alumno),arch);
    fclose(arch);
    Arbol arbolIndice;
    crearArbol(&arbolIndice);
    cargarArbolDesordenado(&arbolIndice, "alumnos.dat");
    recorrerEnOrdenRecArbolBinBusq(&arbolIndice,0, NULL, accionMostrarIndice);
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

        switch(op)
        {
        case 1: {
            int dni;
            printf("Ingrese DNI a dar de baja: ");
            scanf("%d", &dni);
            darDeBaja(&arbolIndice, dni, "alumnos.dat");
            recorrerEnOrdenRecArbolBinBusq(&arbolIndice,0, NULL, accionMostrarIndice);
            break;
        }
        case 2:
            grabarArbolEnArchivo(&arbolIndice, "alumnos.idx");
            break;
        case 3:
            vaciarArbol(&arbolIndice);
            break;
        case 4:
            printf("\nAdios");
        }
    }while(op != 4);
    return 0;
}
