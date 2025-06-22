#include <stdio.h>
#include <stdlib.h>
#include "lote.h"

int main()
{
    int op;
    float por;
    Lote lotes[] = {
    {"L001",2,"OK"},
    {"L001",3,"OK"},
    {"L001",1,"FALLA"},
    {"L001",5,"OK"},
    {"L002",2,"OK"},
    {"L002",1,"OK"},
    {"L002",3,"OK"},
    {"L003",1,"FALLA"},
    {"L003",2,"OK"},
    {"L003",3,"OK"},
    {"L003",6,"FALLA"},
    {"L004",2,"OK"},
    {"L004",3,"OK"},
    {"L004",1,"FALLA"},
    {"L004",5,"OK"}
    };
    FILE* arch = fopen("entrada.bin", "wb");
    if(!arch)
    {
        printf("\nError al abrir archivo");
        return 0;
    }
    fwrite(lotes,sizeof(Lote),sizeof(lotes) / sizeof(Lote), arch);

    fclose(arch);


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
            scanf("%f", &por);
            break;
        case 2:
            procesarArch("entrada.bin",por);
            break;
        case 3:
            mostrarArch("entrada.bin");
            break;
        }


    }while(op != 5);

    printf("\nAdios");
}
