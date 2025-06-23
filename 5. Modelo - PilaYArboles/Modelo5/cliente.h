#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



#endif // CLIENTE_H_INCLUDED
