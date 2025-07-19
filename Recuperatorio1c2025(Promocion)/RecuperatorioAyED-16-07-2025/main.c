#include <stdio.h>
#include <stdlib.h>
#include "utilitaria.h"
#include "lista.h"
#include "arbol_bin_busq.h"

int main()
{

    abrirYMostrar10Pacientes();
    tArbolBinBusq arbolIdx;
    crearArbolBinBusq(&arbolIdx);
    cargarArbolIdx(&arbolIdx, "pacientes.dat");
    FILE* archPacientes = fopen("pacientes.dat", "rb+");
    int op;

    do
    {
        printf("\n---Menu---");
        printf("\n1-Insertar nuevo paciente");
        printf("\n2-Eliminar paciente");
        printf("\n3-Nueva consulta");
        printf("\n4-Salir");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            printf("\nOpcion 1");
            darAlta(&arbolIdx,archPacientes);
            break;
        case 2:
            int eliminar;
            printf("\nOpcion eliminar nroReg:");
            scanf("%d", &eliminar);
            darDeBaja(&arbolIdx,eliminar,archPacientes);
            break;
        case 3:
            printf("\nGenerar consultas");
            generarConsulta(&arbolIdx,archPacientes);
            break;
        case 4:
            printf(("\nSaliste"));
            break;
        }
    }while(op != 4);
    fclose(archPacientes);
    //abrirYMostrarPacientes();
    abrirYMostrar10Pacientes();
    return 0;
}

