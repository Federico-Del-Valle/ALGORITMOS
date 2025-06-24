#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Pila;

void crearPila(Pila* p);
void vaciarPila(Pila* p);

int ponerEnPila(Pila* p, void* dato, unsigned tamDato);
int sacarDePila(Pila* p, void* dato, unsigned tamDato);

#endif // PILA_H_INCLUDED
