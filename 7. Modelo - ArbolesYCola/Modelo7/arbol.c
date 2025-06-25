#include "arbol.h"
#include "persona.h"


void crearArbol(Arbol* p)
{
    *p = NULL;
}

int ponerEnArbol(Arbol* p, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*), int(*accion)(void*, unsigned, void*))
{
    NodoArbol* nue;
    int rc;
    if(!*p)
    {
        if((nue= malloc(sizeof(NodoArbol)))== NULL || (nue->info = malloc(tamDato)) == NULL)
        {
            free(nue);
            return 0;
        }
        memcpy(nue->info,dato,tamDato);
        nue->tamInfo = tamDato;
        nue->izq= NULL;
        nue->der = NULL;
        *p = nue;
        return 1;
    }

    while(*p)
    {
        if((rc = cmp(dato, (*p)->info)) < 0)
            return ponerEnArbol(&(*p)->izq, dato, tamDato,cmp,NULL);
        else if (rc > 0)
            return ponerEnArbol(&(*p)->der, dato, tamDato, cmp, NULL);
        else
            return 2;
    }
    if((nue = malloc(sizeof(NodoArbol))) == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;
    nue->izq= NULL;
    nue->der= NULL;
    *p = nue;
    return 1;
}

int compararPorDni(const void* dato1, const void* dato2)
{
    const Persona* per1 = (const Persona*)dato1;
    const Persona* per2 = (const Persona*)dato2;

    return per1->dni - per2->dni;
}


int eliminarPorDni(Arbol* p, int dni, void* eliminado, unsigned tamElim)
{
    if(!*p)
    return 0;
    Persona* per = (Persona*)(*p)->info;
    if(per->dni > dni)
        return eliminarPorDni(&(*p)->izq, dni,eliminado,tamElim);
    else if(per->dni < dni)
        return eliminarPorDni(&(*p)->der, dni, eliminado, tamElim);
    else
    {
        NodoArbol* elim = *p;

        //tiene un solo hijo

        if(!elim->izq)
            *p = elim->der;
        else if(!elim->der)
                *p = elim->izq;
        else
        {
            int altIzq = alturaArbol(&elim->izq);
            int altDer= alturaArbol(&elim->der);
            NodoArbol** reem;
            if(altIzq > altDer)
            {
                reem = &elim->izq;
                while((*reem)->der)
                    reem = &(*reem)->der;
            }
            else
            {
                reem = &elim->der;
                while((*reem)->izq)
                    reem = &(*reem)->izq;
            }

            void* nuevoDato = malloc((*reem)->tamInfo);
            memcpy(nuevoDato, (*reem)->info, (*reem)->tamInfo);

            free(elim->info);
            elim->info = nuevoDato;
            return eliminarPorDni(reem, ((Persona*)nuevoDato)->dni, eliminado, tamElim);
        }
        memcpy(eliminado,elim->info, tamElim);
        free(elim->info);
        free(elim);
    }
    return 1;
}

int alturaArbol(const Arbol* p)
{
    if(*p)
        return 0;
    int hl = alturaArbol(&(*p)->izq);
    int hd = alturaArbol(&(*p)->der);

    return 1 + (hl > hd ? hl : hd);
}

int mostrarPersona(void* dato, unsigned tamDato, void* param)
{
    const Persona* persona = (const Persona*)dato;
    printf("\n %-20s %-8d %-10d", persona->nombre, persona->edad, persona->dni);
    return 1;
}


void recorrerArbol(Arbol* p, unsigned n, int(*accion)(void* , unsigned n, void*))
{
    if(!*p)
        return;
    recorrerArbol(&(*p)->izq, n+1, accion);
    accion((*p)->info,(*p)->tamInfo, NULL);
    recorrerArbol(&(*p)->der, n+1, accion);
}
