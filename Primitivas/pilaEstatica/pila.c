#include "pila.h"

#define minimo(x, y) ((x) <= (y) ? (x) : (y))

void crearPila(Pila* p)
{
    p->tope = TAM_PILA; //Inicializo la pila
}

void vaciarPila(Pila* p)
{
    p->tope = TAM_PILA; //Vuelvo la pila al inicio
}

int pilaVacia(const Pila* p)
{
    return p->tope == TAM_PILA; //Si el tope es igual al tamaño total, esta vacia
}

int pilaLlena(const Pila* p, unsigned cantBytes)
{
    return p->tope < cantBytes + sizeof(unsigned); //Si mi espacio no es suficiente para almacenar mas, esta llena
}

int verTope(const Pila* p, void* d, unsigned cantBytes)
{
    unsigned tamInfo;

    if(p->tope == TAM_PILA) //Verifica si la pila esta vacia
        return 0;

    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned)); //Copio el tamaño del elemento, el cual se encuentra en p->pila + p->tope
    memcpy(d, p->pila + p->tope + sizeof(unsigned), minimo(cantBytes, tamInfo)); //Copio los datos del primer elemento, con minimo para no copiar de mas
    return 1;
}

int ponerEnPila(Pila* p, const void* d, unsigned cantBytes)
{
    if(p->tope < cantBytes + sizeof(unsigned)) //Verifica si la pila esta llena
        return 0;

    p->tope -= cantBytes; //Ajusta el tope para agregar un nuevo elemento
    memcpy(p->pila + p->tope, d, cantBytes); //Copio el elemento en su lugar reservado
    p->tope -= sizeof(unsigned); //Ajusto el tope para ALMACENAR EL TAMAÑO del elemento
    memcpy(p->pila + p->tope, &cantBytes, sizeof(unsigned)); //Copio el tamaño del elemento en su lugar
    return 1;
}

int sacarDePila(Pila* p, void* d, unsigned cantBytes)
{
    unsigned tamInfo;

    if(p->tope == TAM_PILA) //Verifica si la pila esta vacia
        return 0;

    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned)); //Copio el tamaño del primer elemento en tamInfo
    p->tope += sizeof(unsigned); //Ajusto el tope hacia arriba (voy a tener mas espacio al eliminar)
    memcpy(d, p->pila + p->tope, minimo(cantBytes, tamInfo)); //Copio el contenido que voy a eliminar por si lo necesito
    p->tope += tamInfo; //Ajusto el tope hacia arriba y queda eliminado

    return 1;
}
