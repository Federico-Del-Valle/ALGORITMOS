#include <stdio.h>
#include <stdlib.h>

int main()
{
    int op;
    int por;


    do
    {
        printf("--MENU--");
        printf("\n1-Ingrese el porcentaje que desea cumplir-");
        printf("\n2-Procese los archivos y genere los archivos resultantes-");
        printf("\n3-Mostrar archivo de entrada-");
        printf("\n4-Mostrar archivos de salida");
        printf("\n5-Salir");
        printf("\n\nSeleccion una opcion");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            printf("\nIngrese el porcentaje");
            scanf("%d", &por);
            break;
        case 2:
            procesarArch("entrada.bin");
            break;
        case 3:
            mostrarArch("entrada.bin");
            break;
        case 4:
            mostrarArchSalida();
            break;
        default:
            printf("\nOpcion invalida!");
        }


    }while(op != 5);

    printf("\nAdios");
}
