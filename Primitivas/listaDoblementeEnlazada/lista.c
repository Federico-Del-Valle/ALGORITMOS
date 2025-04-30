#include "lista.h"

void crearLista(Lista* p)
{
    *p = NULL;
}

int vaciarLista(Lista* p)
{
    int cant = 0;
    Nodo* act = *p;

    if(act)
    {
        while(act->ant)
            act = act->ant;
        while(act)
        {
            Nodo* aux = act->sig;

            free(act->info);
            free(act);
            act = aux;
            cant++;
        }
        *p = NULL;
    }
    return cant;
}

int listaLlena(const Lista* p, unsigned cantBytes)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* aux = malloc(cantBytes);

    free(nue);
    free(aux);

    return aux == NULL || nue == NULL;
}

int listaVacia(const Lista* p)
{
    return *p == NULL;
}

int ponerAlComienzo(Lista* p, const void* d, unsigned cantBytes)
{
    Nodo* act = *p;
    Nodo* nue;

    if(act)
        while(act->ant)
            act = act->ant;
    if((nue = malloc(sizeof(Nodo))) == NULL ||
       (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = act;
    nue->ant = NULL;
    if(act)
        act->ant = nue;
    *p = nue;

    return 1;
}

int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes)
{
    Nodo* act = *p;
    Nodo* nue;

    if(act)
        while(act->sig)
            act = act->sig;
    if((nue = malloc(sizeof(Nodo))) == NULL ||
       (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    nue->ant = act;
    if(act)
        act->sig = nue;
    *p = nue;

    return 1;
}

int ponerEnOrden(Lista* p, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*),
                 int(*Acumular)(void**, unsigned*, const void*, unsigned))
{
    Nodo* act = *p;
    Nodo* sig;
    Nodo* ant;
    Nodo* nue;

    if(act == NULL)
    {
        ant = NULL;
        sig = NULL;
    }
    else
    {
        int aux;
        while(act->sig && Comparar(act->info, d) < 0)
            act = act->sig;
        while(act->ant && Comparar(act->info, d) > 0)
            act = act->ant;
        aux = Comparar(act->info, d);

        if(aux == 0)
        {
            *p = act;
            if(Acumular)
                if(Acumular(&act->info, &act->tamInfo, d, cantBytes) == 0)
                    return SIN_MEM;
            return CLA_DUP;
        }
        if(aux < 0)
        {
            ant = act;
            sig = act->sig;
        }
        else
        {
            ant = act->ant;
            sig = act;
        }
    }
    if((nue = malloc(sizeof(Nodo))) == NULL ||
       (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = sig;
    nue->ant = ant;
    if(sig)
        sig->ant = nue;
    if(ant)
        ant->sig = nue;
    *p = nue;

    return TODO_OK;
}

int mostrarDeIzqADer(const Lista* p, void(*Mostrar)(const void*))
{
    Nodo* act = *p;
    int cant = 0;

    if(act)
    {
        Mostrar(NULL);
        while(act->ant)
            act = act->ant;
        while(act)
        {
            Mostrar(act->info);
            act = act->sig;
            cant++;
        }
    }
    return cant;
}

int mostrarDeDerAIzq(const Lista* p, void(*Mostrar)(const void*))
{
    Nodo* act = *p;
    int cant = 0;

    if(act)
    {
        Mostrar(NULL);
        while(act->sig)
            act = act->sig;
        while(act)
        {
            Mostrar(act->info);
            act = act->ant;
            cant++;
        }
    }
    return cant;
}

void ordenarLista(Lista* p, int(*Comparar)(const void*, const void*))
{
    Nodo* act = *p;
    Nodo* sup = NULL;
    Nodo* inf = NULL;
    int marca = 1;

    if(act == NULL)
        return;
    while(act->ant)
        act = act->ant;

    while(marca)
    {
        marca = 0;
        while(act->sig != sup)
        {
            if(Comparar(act->info, act->sig->info) > 0)
            {
                void* inf = act->info;
                unsigned tam = act->tamInfo;

                marca = 1;
                act->info = act->sig->info;
                act->sig->info = inf;
                act->tamInfo = act->sig->tamInfo;
                act->sig->tamInfo = tam;
            }
            act = act->sig;
        }
        sup = act;

        while(act->ant != inf)
        {
            if(Comparar(act->info, act->ant->info) < 0)
            {
                void* inf = act->info;
                unsigned tam = act->tamInfo;

                marca = 1;
                act->info = act->ant->info;
                act->ant->info = inf;
                act->tamInfo = act->ant->tamInfo;
                act->ant->tamInfo = tam;
            }
            act = act->ant;
        }
        inf = act;
    }
}

int eliminarPorClave(Lista* p, void* d, unsigned cantBytes,
                     int(*Comparar)(const void*, const void*))
{
    Nodo* act = *p;
    int aux;

    if(act == NULL) //Lista vacia
        return 0;

    while(act->sig && Comparar(act->info, d) < 0)
        act = act->sig;

    while(act->ant && Comparar(act->info, d) > 0)
        act = act->ant;

    aux = Comparar(act->info, d);

    if(aux == 0) //Encontro la clave
    {
        Nodo* ant = act->ant;
        Nodo* sig = act->sig;

        if(ant)
            ant->sig = sig;
        if(sig)
        {
            sig->ant = ant;
            *p = sig;
        }
        else
            *p = ant;

        memcpy(d, act->info, cantBytes);
        free(act->info);
        free(act);
        return 1;
    }
    return 0;
}
