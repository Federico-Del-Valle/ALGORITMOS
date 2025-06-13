#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#define minimo(x,y) ((x) < (y) ? (x) : (y))

typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Pila;

void crearPila(Pila* p);
void vaciarPila(Pila* p);

int ponerEnPila(Pila* p, void* dato, unsigned tamDato);
int sacarDePila(Pila* p, void* dato, unsigned tamDato);

int pilaVacia(const Pila*p);

#endif // PILA_H_INCLUDED
