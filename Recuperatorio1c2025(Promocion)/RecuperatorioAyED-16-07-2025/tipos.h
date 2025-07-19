#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIN_MEM         1
#define CLA_DUP         2
#define TODO_BIEN       0

typedef struct {
    long dni;
    char nombreApellido[60];
    char obraSocial[15];
    int numeroPaciente;
    int cantidadConsultas;
    float montoInvertido;
} tPaciente;

typedef struct sNodo
{
    void           *info;
    unsigned        tamInfo;
    struct sNodo   *sig;
} tNodo;


typedef struct
{
    tNodo  *pri,
           *ult;
} tCola;

typedef tNodo *tPila;

typedef tNodo *tLista;

#endif // TIPOS_H_INCLUDED
