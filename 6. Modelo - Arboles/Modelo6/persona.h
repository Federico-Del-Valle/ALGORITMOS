#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include "arbol.h"

typedef struct
{
    int dni;
    char nombre[30];
    int edad;
}Persona;


int cargarArbol(Arbol* a, const char nombre[]);
int eliminarDni(Arbol*, int);





#endif // PERSONA_H_INCLUDED
