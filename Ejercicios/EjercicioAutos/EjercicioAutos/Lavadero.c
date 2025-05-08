#include"Lavadero.h"
void inicializarLavadero(Lavadero* l)
{
    crearCola(&l->cola);
    l->cantidad = 0;
    l->tiempoTotal=0;
}

int encolarAuto(Lavadero* l, const Vehiculo* v)
{
    if(ponerEnCola(&l->cola,v, sizeof(Vehiculo)))
    {
        l->cantidad++;
        l->tiempoTotal += v->tiempo;
        return 1;
    }
    return 0;
}

int atenderAuto(Lavadero* l, Vehiculo* v)
{
    if(sacarDeCola(&l->cola, v, sizeof(Vehiculo)))
    {
        l->cantidad--;
        l->tiempoTotal-=v->tiempo;
        return 1;
    }
    return 0;
}

void vaciarLavadero(Lavadero* l)
{
    vaciarCola(&l->cola);
    l->cantidad =0;
    l->tiempoTotal = 0;
}
int contarCola(const Lavadero* l) {
    return l->cantidad;
}

int contarTiempo(const Lavadero* l) {
    return l->tiempoTotal;
}
