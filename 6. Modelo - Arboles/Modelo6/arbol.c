#include "arbol.h"
#include "persona.h"

void crearArbol(Arbol* p)
{
    *p = NULL;
}

int ponerEnArbolRec(Arbol* p, void* dato, unsigned tamDato,int(*cmp)(const void*, const void*), int(*acumular)(void*, void*))
{
    NodoArbol* nue;
    int rc;
    if(!*p)
    {
        if((nue = malloc(sizeof(NodoArbol))) == NULL || (nue->info = malloc(tamDato)) == NULL)
        {
            printf("\nERROR");
            free(nue);
            return 0;
        }
        memcpy(nue->info, dato, tamDato);
        nue->tamInfo = tamDato;
        nue->der =NULL;
        nue->izq = NULL;
        *p = nue;

        return 1;
    }

    while(*p)
    {
        if((rc = cmp(dato, (*p)->info)) < 0)
        {
            return ponerEnArbolRec(&(*p)->izq, dato, tamDato, cmp,NULL);
        }
        else if(rc > 0)
            return ponerEnArbolRec(&(*p)->der, dato, tamDato, cmp,NULL);
        else
            return 2;
    }

    if((nue = malloc(sizeof(NodoArbol))) == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info,dato, tamDato);
    nue->tamInfo = tamDato;
    *p = nue;
    nue->der = NULL;
    nue->izq = NULL;

    return 1;
}


int compararPorDni(const void* dato1, const void* dato2)
{
    const Persona* persona = (const Persona*)dato1;
    const Persona* persona2 = (const Persona*)dato2;

    return persona->dni - persona2->dni;
}


void recorrerEnOrden(Arbol* p, unsigned n, int(*accion)(const void*,unsigned, const void*))
{
    if(!*p)
        return;
    recorrerEnOrden(&(*p)->izq,n+1,accion);
    accion((*p)->info,(*p)->tamInfo ,NULL);
    recorrerEnOrden(&(*p)->der, n+1, accion);
}


int mostrarPersona(const void* dato, unsigned tamDato, const void* param)
{
    const Persona* per = (Persona*)dato;
    printf("\nLos datos son: %s %d %d", per->nombre, per->edad, per->dni);
    return 1;
}

