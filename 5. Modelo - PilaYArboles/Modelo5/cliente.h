#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"
#include "Pila.h"


typedef struct
{
    int idCliente;
    Pila reclamos;
}Cliente;

typedef struct
{
    int idCliente;
    int idReclamo;
    char descripcion[100];
}Reclamo;

int procesarArch(const char nombre[], Arbol* arbol);
void procesarArchTexto(void* info, unsigned tamInfo, unsigned nivel, void* params);
int compararPorId(const void* dato1, const void* dato2);
int acumular(void* dato, const void* dato2);
#endif // CLIENTE_H_INCLUDED
