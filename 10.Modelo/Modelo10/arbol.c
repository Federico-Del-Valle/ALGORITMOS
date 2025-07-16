#include "arbol.h"

void iniciarArbol(Arbol* p)
{
    *p=NULL;
}
int insertarEnArbol(Arbol* p, void* d, unsigned tam, int(*cmp)(const void*, const void*))
{
    nodoArbol* nue;
    int rc;
    while(*p)
    {
        if((rc=cmp(d,(*p)->info)) < 0)
        {
            return insertarEnArbol(&(*p)->izq,d,tam,cmp);
        }
        else if(rc > 0)
            return insertarEnArbol(&(*p)->der, d, tam,cmp);
        else
            return 2; //duplicado
    }
    if((nue = malloc(sizeof(nodoArbol))) == NULL || (nue->info = malloc(sizeof(tam))) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, tam);
    nue->tamInfo = tam;
    nue->der = NULL;
    nue->izq = NULL;
    *p = nue;
    return 1;
}

nodoArbol** buscarNodo(Arbol* p, const void* d, int(*cmp)(const void*, const void*))
{
    int rc;
    if(!*p)
        return NULL;
    if(*p && (rc=cmp(d,(*p)->info)))
    {
        if(rc < 0)
            return buscarNodo(&(*p)->izq,d,cmp);
        return buscarNodo(&(*p)->der,d,cmp);
    }
    return (nodoArbol**)p;
}

int buscarElemArbol(Arbol* p, void* d, unsigned tam, int(*cmp)(const void*, const void*))
{
    if(!(p= buscarNodo(p,d,cmp)))
        return 0;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}
int eliminarElem(Arbol* p, void* d, unsigned tam, int(*cmp)(const void* , const void*))
{
    if(!(p=buscarNodo(p,d,cmp)))
        return 0;
    memcpy(d,(*p)->info, MINIMO(tam,(*p)->tamInfo));
    return eliminarRaiz(p);
}

void vaciarArbol(Arbol* p)
{
    if(!*p)
        return;
    vaciarArbol(&(*p)->der);
    vaciarArbol(&(*p)->izq);
    free((*p)->info);
    free(*p);
    *p = NULL;

}
int eliminarRaiz(Arbol* p)
{
    nodoArbol** remp;
    nodoArbol* elim;
    if(!*p)
        return 0;
    free((*p)->info);
    if(!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return 1;
    }
    remp= alturaArbol(&(*p)->izq) > alturaArbol(&(*p)->der) ? mayorNodo(&(*p)->izq) : menorNodo(&(*p)->der);
    elim = *remp;
    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;
    *remp = elim->izq ? elim->izq : elim->der;
    free(elim);
    return 1;
}

int esCompletoHataNivel(const Arbol* p, int n)
{
    if(*p)
        return n < 0;
    if(n==0)
        return 1;
    return esCompletoHataNivel(&(*p)->izq, n-1) && esCompletoHataNivel(&(*p)->der, n-1);
}

int esCompleto(const Arbol* p)
{
    return esCompletoHataNivel(p,alturaArbol(p)-1);
}
int esBalanceado(const Arbol* p)
{
    return esCompletoHataNivel(p, alturaArbol(p)-2);
}

int esAVL(const Arbol* p)
{
    int hi,hd;
    if(!*p)
        return 1;
    hi= alturaArbol(&(*p)->izq);
    hd= alturaArbol(&(*p)->der);
    if(abs(hi - hd)> 1)
        return 0;
    return esAVL(&(*p)->izq) && esAVL(&(*p)->der);
}

int alturaArbol(const Arbol* p)
{
    int hi,hd;
    if(!*p)
        return 0;
    hi= alturaArbol(&(*p)->izq);
    hd = alturaArbol(&(*p)->der);
    return (hi>hd ? hi:hd)+1;
}

nodoArbol** mayorNodo(const Arbol* p)
{
    if(!*p)
        return NULL;
    if(!(*p)->der)
        return (nodoArbol**)p;
    return mayorNodo(&(*p)->der);
}

nodoArbol** menorNodo(const Arbol* p)
{
    if(!*p)
        return NULL;
    if(!(*p)->izq)
        return (nodoArbol**)p;
    return menorNodo(&(*p)->izq);
}

void recorrerArbol(Arbol* p, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*))
{
    if(!*p)
        return;
    recorrerArbol(&(*p)->izq,n+1,params,accion);
    accion((*p)->info, (*p)->tamInfo,n,params);
    recorrerArbol(&(*p)->der,n+1,params,accion);
}




void grabarEnArch(void *info, unsigned tamInfo, unsigned nivel, void *params)
{
    fwrite(info, tamInfo, 1, (FILE*)params);
}

