#include <stdio.h>
#include <stdlib.h>
#include"pilaDinamica.h"
#include"esParentesis.h"


int main()
{
    printf("---INICIA PARCIAL---\n");

    char cadena[100];
    printf("Ingrese una cadena para guardar en el archivo:\n  ");
    fgets(cadena,100,stdin);
    cadena[strcspn(cadena,"\n")] = '\0';
    FILE* arch = fopen("parentesis.txt", "w");
    if(!arch)
    {
        printf("Error al abrir el archivo");
        return 1;
    }
    fprintf(arch,"%s", cadena);
    fclose(arch);
    Pila p;
    crearPila(&p);
    if(chequearSiEsParentizado("parentesis.txt",&p))
    {
        printf("Esta equilibrado");
    }
    else
    {
        printf("No esta equilibrado");
    }




}
