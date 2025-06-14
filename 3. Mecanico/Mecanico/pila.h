#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#define minimo(x,y) ((x) < (y) ? (x) : (y))

typedef struct NodoPila
{
    void* dato;
    unsigned tamDato;
    struct NodoPila* sig;
}NodoPila;

typedef NodoPila* Pila;

void crearPila(Pila* p);
void vaciarPila(Pila* p);

int ponerEnPila(Pila* p, void* dato, unsigned tamDato);
int sacarDePila(Pila* p, void* dato, unsigned tamDato);

int pilaVacia(const Pila*p);

#endif // PILA_H_INCLUDED
