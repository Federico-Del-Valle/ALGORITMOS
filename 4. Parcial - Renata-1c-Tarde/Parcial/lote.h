#ifndef LOTE_H_INCLUDED
#define LOTE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char codLote[5];
    int idCod;
    char resultadoCtrl[6];
}Lote;


void procesarArch(const char arch[], int por)
{
    FILE* archivo = fopen(arch, "rb");
    if(!archivo)
    {
        printf("\nError al abrir el archivo %s", arch);
        return;
    }
    Lista listaOK;
    crearLista(&listaOK);
    Lista (&listaFALLA);
    crearLista(&listaFALLA);

    int total = 0;
    int cantOk = 0;
    int primerRegistro = 1;

    Lote actual;

    while(!feof(archivo))
    {
        fread(&actual, sizeof(actual),1, archivo);
        if(primerRegistro || strcmp(actual.codLote, anterior.codLote) == 0)
        {
            if(strcmp(actual.resultadoCtrl, "OK") == 0)
            {
                insertarOrdenado(&listaOK, actual.idCod, compararPorId,  )
                cantOk++;
            }
            else
            {
                insertarOrdenado(&listaFalla, actual);
            }

        }
    }


}



#endif // LOTE_H_INCLUDED
