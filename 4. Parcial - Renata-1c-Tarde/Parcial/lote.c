#include "lote.h"
int compararPorIdProducto(const void* a, const void* b)
{
    const Lote* lote1 = (const Lote*)a;
    const Lote* lote2 = (const Lote*)b;

    return lote1->idCod - lote2->idCod;
}


void procesarArch(const char arch[], float por)
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
            anterior = actual;
            primerRegistro = 0;
        }
        else
        {
            primerRegistro = 1;
            printf("\nEl porcentaje a superar es %f\n", por);
            float porcentaje = ((float)cantOk / (float)total) * 100.0;
            printf("\n%f\n", porcentaje);
            if(((float)cantOk / (float)total) * 100.0 > por)
            {
                printf("\nSupera el porcentaje solicitado\n");
                while(sacarDeLista(&listaFALLA,&actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados, "%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
                while(sacarDeLista(&listaOK,&actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados,"%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
            }
            else
            {
                printf("\nNo supera el porcentaje solicitado");
                while(sacarDeLista(&listaFALLA,&actual, sizeof(Lote)))
                {
                    fprintf(archivoObservados, "%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
                while(sacarDeLista(&listaOK,&actual, sizeof(Lote)))
                {
                    fprintf(archivoObservados,"%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
            }
            vaciarLista(&listaFALLA);
            vaciarLista(&listaOK);
            crearLista(&listaFALLA);
            crearLista(&listaOK);

        }


    }
    if(total > 0)
    {
        if(((float)cantOk / (float)total) * 100.0 > por)
            {
                printf("\nSupera el porcentaje solicitado");
                while(sacarDeLista(&listaFALLA,&actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados, "%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
                while(sacarDeLista(&listaOK,&actual, sizeof(Lote)))
                {
                    fprintf(archivoAprobados,"%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
            }
            else
            {
                printf("\nNo supera el porcentaje solicitado");
                while(sacarDeLista(&listaFALLA,&actual, sizeof(Lote)))
                {
                    fprintf(archivoObservados, "%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
                while(sacarDeLista(&listaOK,&actual, sizeof(Lote)))
                {
                    fprintf(archivoObservados,"%s,%d,%s\n", actual.codLote, actual.idCod, actual.resultadoCtrl);
                }
            }


    }
    fclose(archivo);
    fclose(archivoAprobados);
    fclose(archivoObservados);

}


void mostrarArch(const char nombre[])
{
    FILE* arch = fopen(nombre, "r");
    if(!arch)
    {
        printf("\nError al abrir el archivo");
        return ;
    }

    Lote registro;
    printf("\n\n %-10s %-10s %-10s", "IdLote", "IdProd", "Estado");
    while(fread(&registro, sizeof(Lote), 1, arch) == 1)
    {
        printf("\n %-10s %-10d %-10s", registro.codLote, registro.idCod, registro.resultadoCtrl);

    }
    fclose(arch);

}
