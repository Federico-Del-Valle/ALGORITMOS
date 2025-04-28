#include "ColaD.h"
//Crear cola recibe el puntero a la cola y declara los dos punteros en NULL;
void crearCola(Cola* c)
{
    c->pri = NULL;
    c->ult = NULL;
}

int colaLlena(Cola* c, unsigned tamDato)
{
    Nodo* aux = malloc(sizeof(Nodo));
    void* dato = malloc(tamDato);
    free(aux);
    free(dato);
    return aux==NULL || dato == NULL;
}

int ponerEnCola(Cola* c, const void* dato, unsigned tamDato )
{
    Nodo* nue = malloc(sizeof(Nodo));
    if(nue == NULL || ((nue->dato = malloc(tamDato)) == NULL))
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    if(c->ult)
    {
        c->ult->sig = nue;
    }
    else
    {
        c->pri = nue;
    }

    c->ult = nue;
     return 1;
}

int sacarCola(Cola* c, void* dato, unsigned tamDato)
{
    //aux apunta al primer nodo (el que vamos a extraer).
    Nodo* aux = c->pri;
    // Si la cola está vacía, retornamos 0 (no hay nada para sacar).
    if(aux == NULL)
        return 0;
    //Avanzamos el puntero de la cola al siguiente nodo, dejando atrás el que vamos a liberar.
    c->pri = aux->sig;
    //Copiamos el contenido del nodo al buffer del usuario, sin pasarnos del límite. Muy bien aplicado minimo.
    memcpy(dato, aux->dato, minimo(aux->tamDato, tamDato));
    //Liberamos la memoria del dato y del nodo.
    free(aux->dato);
    free(aux);
    // Si al avanzar la cola no quedaron más nodos, también actualizamos el ult para dejar la cola completamente vacía
    if(c->pri == NULL)
        c->ult = NULL;
    return 1;
}

void vaciarCola(Cola* c)
{
    while(c->pri)
    {
        Nodo* aux = c->pri;
        c->pri = aux->sig;
        free(aux->dato);
        free(aux);
    }
    c->ult = NULL;
}

int verPrimeroCola(Cola* c, void* dato, unsigned tamDato)
{
    if(c->pri == NULL)
        return 0;
    memcpy(dato, c->pri->dato, minimo(tamDato, c->pri->tamDato));
    return 1;
}

int colaVacia(Cola* c)
{
    return c->pri == NULL;
}
