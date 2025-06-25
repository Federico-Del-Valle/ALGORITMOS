#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include "arbol.h"
#include "cola.h"

typedef struct
{
    int dni;
    char nombre[30];
    char apellido[30];
    int edad;
}Persona;

int cargarArbol(Arbol* p, const char nombre[]);
int procesarEliminados(Arbol* p, const char nombre[], Cola* c);
int generarArchivo(Cola* p, const char nombre[]);

#endif // PERSONA_H_INCLUDED
