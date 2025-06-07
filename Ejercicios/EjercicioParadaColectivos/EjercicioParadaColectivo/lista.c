#include "lista.h"

int crearLista(lista* p)
{
    *p = NULL;
}

//vaciarLista que retorna la cantidad de elementos que habia en la lista

int vaciarLista(lista* p)
{
    int cant = 0;
    while(*p)
    {
        cant++;
        Nodo* aux = *p;

        *p = aux->sig;
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

    return aux == NULL || info ==NULL;

}

int ponerEnOrden(Lista* lista, const void* d, unsigned cantBytes, int(*Comparar)(const void*, const void*), int(*Acumular)(void**, unsigned*, const void*, unsigned))
{
    Nodo* nue;
    while(*lista && Comparar((*lista)->info,d) < 0)
     lista = &(*lista)->sig;
     if(*lista && Comparar((*lista)->info, d) < 0)
     {
         if(Acumular)
            if(!Acumular(&(*lista)->info, &(*lista)->tamInfo, cantBytes ))
            return SIN_MEM;
         return CLA_DUP;
     }
     if((nuevo = malloc(sizeof(Nodo))) == NULL || (nuevo->info = malloc(cantBytes)==NULL))
     {
         free(nue)
     }
     memcpy(nue->dato, d, cantBytes);
     nue->tamDato = cantBytes;
     nue->sig = *lista;
     *lista = nuevo;

}

int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes)
{
    Nodo* nue;
    while(*p)
    {
        p= &(*p)->sig;
    }
    if((nuevo = malloc(sizeof(Nodo))) == NULL || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nuevo->info, d, cantBytes);
    nue->tamDato=cantBytesM
    nue->sig= NULLM
    *p = nuevo;
    return 1;
}






