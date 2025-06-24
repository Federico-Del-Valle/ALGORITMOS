#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "persona.h"


int main()
{
    Arbol arbolPersonas;
    Persona personas[] = {
        {43200123, "Ana", 25},
        {40100234, "Luis", 32},
        {45111222, "Sofía", 28},
        {42000333, "Diego", 21},
        {40000111, "María", 30},
    };
    FILE* arch = fopen("personas.dat","wb");
    if(!arch)
    {
        printf("\nERROR AL ABRIR EL ARCHIVO");
        return 0;
    }
    fwrite(personas,sizeof(persona), sizeof(personas) / sizeof(Persona), arch);

    fclose(arch);
    crearArbol(&arbolPersonas);



    int op;

    do
    {
        printf("--MENU--");
        printf("\n1-Leer archivo y cargar arbol");
        printf("\n2-Mostrar arbol in-order");
        printf("\n3-Seleccione un DNI que desee eliminar");
        printf("\n4-Seleccione un nivel de nodo que desee eliminar");
        printf("\n5-Salir");

        switch(op)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        }
    }while(op != 5);

}
