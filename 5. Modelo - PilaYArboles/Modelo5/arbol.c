#include "arbol.h"
#include "cliente.h"

void crearArbol(Arbol* p)
{
    *p = NULL;
}

int insertarArbol(Arbol* p, void* dato, unsigned tamDato,
                  int(*comparar)(const void*, const void*),
                  int(*acumular)(void*, const void*))
{
    NodoArbol* nue;
    int rc;

    while(*p)
    {
        if((rc = comparar(dato, (*p)->info)) < 0)
        {
            return insertarArbol(&(*p)->izq, dato, tamDato,comparar, acumular);
        }
        else if (rc > 0)
        {
            return insertarArbol(&(*p)->der, dato, tamDato, comparar, acumular);
        }
        else
        {
            acumular((*p)->info, dato);
            return 1;
        }
    }
    if((nue = malloc(sizeof(NodoArbol))) == NULL || (nue->info = malloc(tamDato)) == NULL)
        {
            free(nue);
            return 0;
        }
    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;
    nue->der = NULL;
    nue-> izq = NULL;
    *p = nue;
    return 1;
}

void recorrerEnOrdenRecArbolBinBusq(const Arbol * p, unsigned n, void * params, void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenRecArbolBinBusq(&(*p)->der, n+1, params, accion);
}




