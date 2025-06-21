#include "lista.h"

void crearLista(Lista* p)
{
    *p = NULL;
}

void vaciarLista(Lista* p)
{
    while(*p)
    {
        Nodo* aux = *p;
        *p = aux->sig;
        free(aux->dato);
        free(aux);
    }
}


int ponerAlIni(Lista* p, void* dato, unsigned tamDato)
{
    Nodo* nue;
    if((nue = malloc(sizeof(Nodo))) == NULL || (nue->dato = malloc(tamDato))== NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->sig = *p;
    *p = nue;
    return 1;
}


int ponerAlFinal(Lista* p, void* dato, unsigned tamDato)
{
    Nodo* nue;
    while(*p)
    {
        p = &(*p)->sig;
    }
    if((nue = malloc(sizeof(Nodo))) == NULL || (nue->dato = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato , dato, tamDato);
    nue->tamDato = tamDato;
    *p = nue;
    nue->sig =NULL;
    return 1;
}

int ponerEnOrden(Lista* lista, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*),
                 int(*Acumular)(void**, unsigned*, const void*, unsigned))
{
    Nodo* nuevo;

    while(*lista && Comparar((*lista)->info, d) < 0)
        lista = &(*lista)->sig;

    if(*lista && Comparar((*lista)->info, d) == 0)
    {
        if(Acumular)
            if(!Acumular(&(*lista)->info, &(*lista)->tamInfo, d, cantBytes))
                return 0;
        return 2;
    }

    if((nuevo = malloc(sizeof(Nodo))) == NULL || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *lista;
    *lista = nuevo;

    return 1;
}




