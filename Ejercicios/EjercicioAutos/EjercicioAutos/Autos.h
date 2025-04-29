#ifndef AUTOS_H_INCLUDED
#define AUTOS_H_INCLUDED
typedef struct
{
    int contAutos;
    int tiempoTotal;
}contadores;

int contarCola(Cola* c)
{
    int contadores contador;
    contador.contAutos=0;
    contador.tiempoTotal=0;
    Nodo* aux = c->prim;
    while(aux)
    {
        contador.contAutos+=1;
        aux = aux->sig;
    }
}

#endif // AUTOS_H_INCLUDED
