#include <stdio.h>
#include <stdlib.h>
#include "persona.h"
#include "arbol.h"
#include "cola.h"

int main()
{

    Arbol arbolPersonas;
    Cola eliminados;
    crearCola(&eliminados);
    crearArbol(&arbolPersonas);
    int dnis[] = {
        39872123,
        50234678,
        32145678
    };
    Persona personas[] = {
    {45123987, "Juan", "Pérez", 34},
    {39872123, "Lucía", "Gómez", 28},
    {50234678, "Mariano", "López", 45},
    {32145678, "Ana", "Martínez", 39},
    {41239876, "Carlos", "Fernández", 50},
    {37891234, "Laura", "Torres", 31},
    {48912345, "Diego", "Ramírez", 27},
    {42781234, "Sofía", "Díaz", 41},
    {46543210, "Martín", "Silva", 36},
    {39987654, "Valeria", "Acosta", 29}
    };
    FILE * archdnis  = fopen("bajas.dat", "wb");
    FILE * arch  = fopen("personas.dat", "wb");
    if(!arch || !archdnis)
        return 0;

    fwrite(dnis, sizeof(int), sizeof(dnis) / sizeof(int), archdnis);
    fwrite(personas, sizeof(Persona), sizeof(personas) / sizeof(Persona), arch);
    fclose(arch);
    fclose(archdnis);

    //
    int op;

    do
    {
        printf("--MENU--");
        printf("\n1-Leer archivo y cargar arbol");
        printf("\n2-Mostrar arbol in-order");
        printf("\n3-Procese los eliminados");
        printf("\n4-Generar archivo eliminados.txt");
        printf("\n5-Salir");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cargarArbol(&arbolPersonas, "personas.dat");
            break;
        case 2:
            recorrerArbol(&arbolPersonas,0,mostrarPersona);
            break;
        case 3:
            procesarEliminados(&arbolPersonas,"bajas.dat", &eliminados);
            break;
        case 4:
            generarArchivo(&eliminados, "eliminados.txt");

        case 5:
            break;
        }
    }while(op != 5);



    return 0;
}
