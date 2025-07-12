#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TDA_Arbol/TDA_Arbol_Ind.h"
#include "utilidades.h"

#define LOTEPRU     "lote.bin"
#define LOTEPRUORD  "loteOrdenado.bin"
#define ARCHIND     "lote.idx"

int main()
{
    tArbol arbol;
    int clave;

    puts(">>> Generando lote de prueba...");
    if (generarLotePrueba(LOTEPRU) != EXITO)
    {
        fprintf(stderr, "Error al generar lote de prueba.\n");
        return EXIT_FAILURE;
    }
    mostrarPruebaCabe();
    leerArchBin(LOTEPRU, sizeof(tPrueba), mostrarPrueba, NULL);

    puts(">>> Creando Arbol...");
    crearArbol(&arbol);

    clave = 20;
    printf(">>> Cargando contenido del Arbol desde archivo binario (clave > %d)...\n", clave);
    if (cargarArchBinDesArbol(LOTEPRU, &arbol, sizeof(tPrueba), cmpPrueba, filterMenor, &clave) != EXITO)
    {
        fprintf(stderr, "Error al cargar árbol.\n");
        return EXIT_FAILURE;
    }

    puts(">>> Recorriendo arbol INORDEN:");
    mostrarPruebaCabe();
    mapIn(&arbol, mostrarPruebaMap, NULL);

    puts(">>> Creando archivo indice...");
    if(crearArchBinIndice(LOTEPRU,ARCHIND,sizeof(tPrueba),cmpPrueba,obtenerClavePrueba,NULL,NULL) != EXITO)
    {
        fprintf(stderr, "Error al crear archivo índice.\n");
        return EXIT_FAILURE;
    }
    mostrarIndiceCabe();
    leerArchBin(ARCHIND, sizeof(tIndice), mostrarIndice, NULL);

    /*
    puts(">>> Creando indice desde arbol...");
    if (crearIndiceDesdeArbol(ARCHIND, &arbol, obtenerClavePrueba, NULL, NULL) != EXITO)
    {
        fprintf(stderr, "Error al crear archivo índice.\n");
        return EXIT_FAILURE;
    }
    mostrarIndiceCabe();
    leerArchBin(ARCHIND, sizeof(tIndice), mostrarIndice, NULL);
    */

    puts(">>> Mostrando elementos usando archivo indice:");
    mostrarPruebaCabe();
    mapArchBinIndice(LOTEPRU, ARCHIND, sizeof(tPrueba), mostrarPrueba, NULL);

    puts(">>> Buscando por clave:");
    clave = 21;
    tPrueba pr;
    if (busqArchBinIndice(LOTEPRU, ARCHIND, clave, &pr, sizeof(tPrueba)) == EXITO)
        printf("\tElemento encontrado (clave %d): %s (%d)\n", pr.clave, pr.descrip, pr.cant);
    else
        printf("\tElemento con clave %d no encontrado.\n", clave);

    puts(">>> Modificando cantidad del elemento...");
    pr.cant += 10;
    if (modArchBinIndice(LOTEPRU, ARCHIND, clave, &pr, sizeof(tPrueba)) == EXITO)
        printf("\tElemento actualizado correctamente.\n");
    else
        printf("\tError al modificar elemento.\n");

    puts(">>> Confirmando modificación:");
    if (busqArchBinIndice(LOTEPRU, ARCHIND, clave, &pr, sizeof(tPrueba)) == EXITO)
        printf("\tElemento actualizado: %s (%d)\n", pr.descrip, pr.cant);

    printf("\nEXITO");
    return EXITO;
}

