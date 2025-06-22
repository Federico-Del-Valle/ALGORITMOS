#ifndef LOTE_H_INCLUDED
#define LOTE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

typedef struct
{
    char codLote[5];
    int idCod;
    char resultadoCtrl[6];
}Lote;


void procesarArch(const char arch[], float por);
void mostrarArch(const char nombre[]);

#endif // LOTE_H_INCLUDED
