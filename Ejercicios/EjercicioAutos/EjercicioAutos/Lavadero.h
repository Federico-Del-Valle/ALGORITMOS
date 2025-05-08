#ifndef LAVADERO_H_INCLUDED
#define LAVADERO_H_INCLUDED
#include "ColaD.h"

typedef struct
{
    Cola cola;
    int cantidad;
    int tiempoTotal;
}Lavadero;

void inicializarLavadero(Lavadero* );
int encolarAuto(Lavadero* , const Vehiculo* );
int atenderAuto(Lavadero* , Vehiculo* );
void vaciarLavadero(Lavadero* );
int contarCola(const Lavadero*);
int contarTiempo(const Lavadero*);

#endif // LAVADERO_H_INCLUDED
