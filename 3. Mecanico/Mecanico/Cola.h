#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED


typedef struct Nodo
{
    void* dato;
    unsigned tamDato;
    struct Nodo* sig;
}Nodo;
typedef struct Cola
{
    Nodo* pri;
    Nodo* ult;
}Cola;


void iniciarCola(Cola* p);
void vaciarCola(Cola* p);


int ponerEnCola(Cola* p, void* dato, unsigned tamDato);
int sacarDeCola(Cola* p, void* dato, unsigned tamDato);



#endif // COLA_H_INCLUDED
