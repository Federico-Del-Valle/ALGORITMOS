#include "lista.h"

#define minimo(x, y)((x) <= (y) ? (x) : (y))

void crearLista(Lista* p)
{
    *p = NULL;
}

/* void vaciarLista(Lista* p)
{
    while(*p)
    {
        Nodo* aux = *p;

        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
} */ //No retorna la cantidad de elementos eliminados

int vaciarLista(Lista* p)
{
    int cant = 0;
    while(*p)
    {
        Nodo* aux = *p;

        cant++;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
    return cant;
}

int vaciarListaYMostrar(Lista* p, void (*Mostrar)(const void* elem, FILE* arch), FILE* fp)
{
    int cant = 0;
    while(*p) //Mientras hay nodo
    {
        Nodo* aux = *p; //"Memoriza" donde está

        cant++;
        *p = aux->sig;  //Desengancho el nodo

        if(Mostrar && fp) //No falla si no recibe la funcion o el archivo
            Mostrar(aux->info, fp);

        free(aux->info);
        free(aux);
    }
    return cant;
}

int listaLlena(const Lista* p, unsigned cantBytes)
{
    Nodo* aux = malloc(sizeof(Nodo));
    void* info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int listaVacia(const Lista* p)
{
    return *p == NULL;
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
                return SIN_MEM;
        return CLA_DUP;
    }

    if((nuevo = malloc(sizeof(Nodo))) == NULL || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return SIN_MEM;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *lista;
    *lista = nuevo;

    return TODO_OK;
}

int ponerAlComienzo(Lista* p, const void* d, unsigned cantBytes)
{
    Nodo* nuevo;

    if((nuevo = malloc(sizeof(Nodo))) == NULL ||
       (nuevo->info = malloc(cantBytes)) ==  NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *p;
    *p = nuevo;

    return 1;
}

int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes)
{
    Nodo* nuevo;

    while(*p)
        p = &(*p)->sig;

    if((nuevo = malloc(sizeof(Nodo))) == NULL ||
       (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = NULL;
    *p = nuevo;

    return 1;
}

int sacarPrimeroLista(Lista* p, void* d, unsigned cantBytes)
{
    Nodo* aux = *p;

    if(aux == NULL)
        return 0;

    *p = aux->sig;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);

    return 1;
}

int sacarUltimoLista(Lista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;

    while((*p)->sig)
        p = &(*p)->sig;

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    free((*p)->info);
    free(*p);
    *p = NULL;

    return 1;
}

int verPrimeroLista(const Lista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

int verUltimoLista(const Lista* p, void* d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;

    while((*p)->sig)
        p = &(*p)->sig;

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));

    return 1;
}

void ordenarLista(Lista* lista, int(*Comparar)(const void*, const void*))
{
    Lista* primero = lista;

    if(*lista == NULL) //Si no hay lista no se puede ordenar
        return;

    while((*lista)->sig) //Mientras haya siguiente...
    {
        if(Comparar((*lista)->info, (*lista)->sig->info) > 0) //Si el actual es mayor que el siguiente...
        {
            Lista* q = primero; //Prepara para comenzar desde el inicio de la lista
            Nodo* aux = (*lista)->sig; //Toma la direccion del nodo

            (*lista)->sig = aux->sig; //Desvincula el nodo de la lista
            while(Comparar((*q)->info, aux->info) > 0) //Avanza buscando el lugar de insercion
                q = &(*q)->sig;
            aux->sig = *q;
            *q = aux; //Vincula el nodo en la lista
        }
        else
            lista = &(*lista)->sig;
    }
}

int mostrarLista(Lista* lista, void (*Mostrar)(const void*, FILE*), FILE* fp)
{
    int cant = 0;

    while(*lista)
    {
        Mostrar((*lista)->info, fp);
        lista = &(*lista)->sig;
        cant++;
    }
    return cant;
}

int mostrarListaAlReves(Lista* lista, void (*Mostrar)(const void*, FILE*), FILE* fp) //Recursiva
{
    if(*lista)
    {
        int n = mostrarListaAlReves(&(*lista)->sig, Mostrar, fp);

        Mostrar((*lista)->info, fp);

        return n + 1;
    }
    return 0;
}

int mostrarListaAlRevesYVaciar(Lista* lista, void (*Mostrar)(const void*, FILE*), FILE* fp)
{
    if(*lista)
    {
        int n = mostrarListaAlReves(&(*lista)->sig, Mostrar, fp);

        Mostrar((*lista)->info, fp);
        free((*lista)->info);
        free(*lista);
        *lista = NULL;

        return n + 1;
    }
    return 0;
}
