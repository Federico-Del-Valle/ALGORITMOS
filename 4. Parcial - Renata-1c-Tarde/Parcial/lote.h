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
    FILE* archivoAprobados = fopen("LotesAprobados.txt", "w");
    FILE* archivoObservados = fopen("LotesObservados.txt", "w");
    if(!archivo || !archivoObservados || !archivoAprobados)
    {
        printf("\nError al abrir el archivo %s", arch);
        return;
    }
    Lista listaOK;
    crearLista(&listaOK);
    Lista listaFALLA;
    crearLista(&listaFALLA);

    int total = 0;
    int cantOk = 0;
    int primerRegistro = 1;

    Lote actual;
    Lote anterior;

    while(fread(&actual, sizeof(actual), 1, archivo) == 1)
    {
        if(primerRegistro || strcmp(actual.codLote, anterior.codLote) == 0)
        {
            if(strcmp(actual.resultadoCtrl, "OK") == 0)
            {
                insertarOrdenado(&listaOK, &actual,sizeof(actual), compararPorIdProducto, NULL  );
                cantOk++;
            }
            else
            {
                insertarOrdenado(&listaFALLA, &actual, sizeof(actual), compararPorIdProducto, NULL);
            }
            total++;
        }
        else
        {
            primerRegistro = 1;
            if((cantOk/total)/ 100 > por)
            {
                printf("\nSupera el porcentaje solicitado");
                while(sacarDeLista(&listaFALLA,actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados, "%d,%d,%s", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
                while(sacarDeLista(&listaOK,actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados,"%d,%d,%s", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
            }
            else
            {
                printf("\nNo supera el porcentaje solicitado");
                while(sacarDeLista(&listaFALLA,actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados, "%d,%d,%s", actual->codLote, actual->idCod, actual->resultadoCtrl);
                }
                while(sacarDeLista(&listaOK,actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados,"%d,%d,%s", actual->codLote, actual->idCod, actual->resultadoCtrl);
                }
            }
            vaciarLista(&listaFALLA);
            vaciarLista(&listaOK);
            crearLista(&listaFALLA);
            crearLista(&listaOK);

        }
        primerRegistro = 0;

    }


}



#endif // LOTE_H_INCLUDED
