#include "arbol.h"

NodoArbol** buscarNodoArbolBinBusq(const ArbolBinBusq* p, const void* d,
                                   int(*cmp)(const void*, const void*));

NodoArbol ** mayorNodoArbolBinBusq(const ArbolBinBusq * p);

NodoArbol ** menorNodoArbolBinBusq(const ArbolBinBusq * p);

const ArbolBinBusq * mayorNodoNoClaveArbolBinBusq(const ArbolBinBusq *p, const ArbolBinBusq *mayor,
                                                   int (*cmp)(const void *, const void *));

const ArbolBinBusq * menorNodoNoClaveArbolBinBusq(const ArbolBinBusq *p, const ArbolBinBusq *menor,
                                                int (*cmp)(const void *, const void *));

const ArbolBinBusq * buscarNodoNoClaveArbolBinBusq(const ArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *));

void crearArbolBinBusq(ArbolBinBusq* p)
{
    *p = NULL;
}

int insertarArbolBinBusq(ArbolBinBusq* p, const void* d, unsigned tam,
                         int(*cmp)(const void*, const void*))
{
    NodoArbol* nue;
    int rc;

    while(*p)
    {
        if((rc = cmp(d, (*p)->info)) < 0)
            p = &(*p)->izq;
        else if (rc > 0)
            p = &(*p)->der;
        else
            return CLA_DUP;
    }
    if((nue = malloc(sizeof(NodoArbol))) == NULL ||
       (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);
    nue->der = nue->izq = NULL;
    *p = nue;
    return TODO_OK;
}

int insertarRecArbolBinBusq(ArbolBinBusq* p, const void* d, unsigned tam,
                         int(*cmp)(const void*, const void*))
{
    NodoArbol* nue;
    int rc;

    while(*p)
    {
        if((rc = cmp(d, (*p)->info)) < 0)
            return insertarRecArbolBinBusq(&(*p)->izq, d, tam, cmp);
        else if (rc > 0)
            return insertarRecArbolBinBusq(&(*p)->der, d, tam, cmp);
        else
            return CLA_DUP;
    }
    if((nue = malloc(sizeof(NodoArbol))) == NULL ||
       (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);
    nue->der = nue->izq = NULL;
    *p = nue;
    return TODO_OK;
}

void recorrerEnOrdenRecArbolBinBusq(const ArbolBinBusq * p, unsigned n, void * params,
                                    void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenRecArbolBinBusq(&(*p)->der, n+1, params, accion);
}

void recorrerEnOrdenArbolBinBusq(const ArbolBinBusq * p, void * params,
                                 void (*accion)(void *, unsigned, unsigned, void *))
{
    recorrerEnOrdenRecArbolBinBusq(p, 0, params, accion);
}

void recorrerEnOrdenInversoRecArbolBinBusq(const ArbolBinBusq * p, unsigned n, void * params,
                                           void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenInversoRecArbolBinBusq(&(*p)->der, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenInversoRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
}

void recorrerEnOrdenInversoArbolBinBusq(const ArbolBinBusq * p, void * params,
                                        void (*accion)(void *, unsigned, unsigned, void *))
{
    recorrerEnOrdenInversoRecArbolBinBusq(p, 0, params, accion);
}

void recorrerPreOrdenRecArbolBinBusq(const ArbolBinBusq * p, unsigned n, void * params,
                                     void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerPreOrdenRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
    recorrerPreOrdenRecArbolBinBusq(&(*p)->der, n+1, params, accion);
}

void recorrerPreOrdenArbolBinBusq(const ArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *))
{
    recorrerPreOrdenRecArbolBinBusq(p, 0, params, accion);
}

void recorrerPosOrdenRecArbolBinBusq(const ArbolBinBusq * p, unsigned n,
                                     void * params, void (*accion)(void *, unsigned,
unsigned, void *))
{
    if(!*p)
        return;
    recorrerPosOrdenRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
    recorrerPosOrdenRecArbolBinBusq(&(*p)->der, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
}

void recorrerPosOrdenArbolBinBusq(const ArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void*))
{
    recorrerPosOrdenRecArbolBinBusq(p, 0, params, accion);
}

void recorrerEnOrdenSimpleArbolBinBusq(const ArbolBinBusq * p,
                                       void * params, void (*accion)(void *, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq, params, accion);
    accion((*p)->info, (*p)->tamInfo, params);
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der, params, accion);
}

void recorrerPreOrdenSimpleArbolBinBusq(const ArbolBinBusq * p,
                                        void * params, void (*accion)(void *, unsigned, void *))
{
    if(!*p)
        return;
    accion((*p)->info, (*p)->tamInfo, params);
    recorrerPreOrdenSimpleArbolBinBusq(&(*p)->izq, params, accion);
    recorrerPreOrdenSimpleArbolBinBusq(&(*p)->der, params, accion);
}

void recorrerPosOrdenSimpleArbolBinBusq(const ArbolBinBusq * p,
                                        void * params, void (*accion)(void *, unsigned, void *))
{
    if(!*p)
        return;
    recorrerPosOrdenSimpleArbolBinBusq(&(*p)->izq, params, accion);
    recorrerPosOrdenSimpleArbolBinBusq(&(*p)->der, params, accion);
    accion((*p)->info, (*p)->tamInfo, params);
}

int eliminarRaizArbolBinBusq(ArbolBinBusq *p)
{
    NodoArbol **remp, *elim;

    if (!*p)
        return 0; // ARBOL_VACIO

    free((*p)->info);
    if (!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return 1; // OK
    }

    remp = alturaArbolBin(&(*p)->izq) > alturaArbolBin(&(*p)->der) ?
           mayorNodoArbolBinBusq(&(*p)->izq) :
           menorNodoArbolBinBusq(&(*p)->der);

    elim = *remp;
    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;
    *remp = elim->izq ? elim->izq : elim->der;
    free(elim);
    return 1; // OK
}

int eliminarElemArbolBinBusq(ArbolBinBusq * p, void * d, unsigned tam,
                             int (*cmp)(const void*, const void *))
{
    if(!(p = buscarNodoArbolBinBusq(p,d,cmp)))
        return 0; //NO_EXISTE
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return eliminarRaizArbolBinBusq(p);
}

int buscarElemArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                           int (*cmp)(const void *, const void *))
{
    if(!(p = buscarNodoArbolBinBusq(p,d,cmp)))
        return 0; //NO_EXISTE
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

unsigned leerDesdeArchivoBin(void ** d, void * pf, unsigned pos, void * params)
{
    unsigned tam = *(int*)params;
    *d = malloc(tam);
    if(!*d)
        return 0;
    fseek((FILE*)pf, pos*tam, SEEK_SET);
    return fread(*d, tam, 1, (FILE*)pf);
}

int cargarDesdeDatosOrdenadosRec(ArbolBinBusq* p, void* ds,
                                 unsigned(*leer)(void**, void*, unsigned, void* params),
                                 int li, int ls, void* params)
{
    int m = (li + ls)/2;
    int r;

    if(li > ls)
        return TODO_OK;

    *p = malloc(sizeof(NodoArbol));
    if(!*p || !((*p)->tamInfo = leer(&(*p)->info, ds, m, params)))
    {
        free(*p);
        return SIN_MEM;
    }

    (*p)->izq = (*p)->der = NULL;

    if((r = cargarDesdeDatosOrdenadosRec(&(*p)->izq, ds, leer, li, m - 1, params)) != TODO_OK)
        return r;
    return cargarDesdeDatosOrdenadosRec(&(*p)->der, ds, leer, m + 1, ls, params);
}

int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(ArbolBinBusq * p, FILE * pf,
                                                unsigned tamInfo)
{
    int cantReg;
    if(*p || !pf)
        return 0;
    fseek(pf, 0L, SEEK_END);
    cantReg = ftell(pf)/tamInfo;
    return cargarDesdeDatosOrdenadosRec(p, pf, leerDesdeArchivoBin, 0, cantReg-1, &tamInfo);
}

int cargarArchivoBinOrdenadoArbolBinBusq(ArbolBinBusq * p, const char * path,
                                         unsigned tamInfo)
{
    int cantReg,
        r;
    FILE * pf;
    if(*p)
        return SIN_INICIALIZAR;
    if(!(pf = fopen(path, "rb")))
        return ERROR_ARCH;
    fseek(pf, 0L, SEEK_END);
    cantReg = ftell(pf)/tamInfo;
    r = cargarDesdeDatosOrdenadosRec(p, pf, leerDesdeArchivoBin, 0, cantReg-1, &tamInfo);
    fclose(pf);
    return r;
}

int cargarDesdeDatosOrdenadosArbolBinBusq(ArbolBinBusq *p,
                                          void *ds, unsigned cantReg,
                                          unsigned (*leer)(void **, void *, unsigned, void *params),
                                          void *params)
{
    if(*p || !ds)
        return 0;
    return cargarDesdeDatosOrdenadosRec(p, ds, leer, 0, cantReg - 1, params);
}

NodoArbol** buscarNodoArbolBinBusq(const ArbolBinBusq* p, const void* d,
                                   int(*cmp)(const void*, const void*))
{
    int rc;
    while(*p && (rc = cmp(d, (*p)->info)))
    {
        if(rc < 0)
            p = &(*p)->izq;
        else
            p = &(*p)->der;
    }
    if(!*p)
        return NULL;
    return (NodoArbol**)p;
}

NodoArbol ** buscarRecNodoArbolBinBusq(const ArbolBinBusq * p, const void * d, int (*cmp) (const void *, const void *))
{
    int rc;
    if(!*p)
        return NULL;
    if(*p && (rc=cmp(d, (*p)->info)))
    {
        if(rc<0)
            return buscarRecNodoArbolBinBusq(&(*p)->izq, d, cmp);
        return buscarRecNodoArbolBinBusq(&(*p)->der, d, cmp);
    }
    return (NodoArbol **) p;
}

NodoArbol ** mayorNodoArbolBinBusq(const ArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    while((*p)->der)
        p = &(*p)->der;
    return (NodoArbol **) p;
}

NodoArbol ** menorNodoArbolBinBusq(const ArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    while((*p)->izq)
        p = &(*p)->izq;
    return (NodoArbol **) p;
}

NodoArbol ** mayorRecNodoArbolBinBusq(const ArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    if(!(*p)->der)
        return (NodoArbol **) p;
    return mayorRecNodoArbolBinBusq(&(*p)->der);
}

NodoArbol ** menorRecNodoArbolBinBusq(const ArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    if(!(*p)->izq)
        return (NodoArbol **) p;
    return menorRecNodoArbolBinBusq(&(*p)->izq);
}

int mayorElemNoClaveArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *))
{
    const ArbolBinBusq *mayor = p;
    if (!*p)
        return 0;
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->izq, mayor, cmp);
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->der, mayor, cmp);

    memcpy(d, (*mayor)->info, MINIMO(tam, (*mayor)->tamInfo));
    return 1;
}

const ArbolBinBusq * mayorNodoNoClaveArbolBinBusq(const ArbolBinBusq *p, const ArbolBinBusq *mayor,
                                                   int (*cmp)(const void *, const void *))
{
    if (!*p)
        return mayor;

    if (cmp((*p)->info, (*mayor)->info) > 0)
        mayor = p;

    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->izq, mayor, cmp);
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->der, mayor, cmp);

    return mayor;
}

int menorElemNoClaveArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                              int (*cmp)(const void *, const void *))
{
    const ArbolBinBusq * menor = p;
    if (!*p)
        return 0;
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->izq, menor, cmp);
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->der, menor, cmp);

    memcpy(d, (*menor)->info, MINIMO(tam, (*menor)->tamInfo));

    return 1;
}

const ArbolBinBusq * menorNodoNoClaveArbolBinBusq(const ArbolBinBusq *p, const ArbolBinBusq *menor,
                                                int (*cmp)(const void *, const void *))
{
    if (!*p)
        return menor;
    if (cmp((*p)->info, (*menor)->info) < 0)
        menor = p;
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->izq, menor, cmp);
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->der, menor, cmp);
    return menor;
}

int buscarElemNoClaveArbolBinBusq(const ArbolBinBusq *p, void *d, unsigned tam,
                                  int (*cmp)(const void *, const void *))
{
    const ArbolBinBusq * busq = NULL;
    if (!*p)
        return 0;

    if(cmp((*p)->info, d) == 0)
        busq = p;
    else if ((busq = buscarNodoNoClaveArbolBinBusq(&(*p)->izq, d, cmp)) == NULL) {
        busq = buscarNodoNoClaveArbolBinBusq(&(*p)->der, d, cmp);
    }

    if (busq == NULL)
        return 0;

    memcpy(d, (*busq)->info, MINIMO(tam, (*busq)->tamInfo));

    return 1;
}

const ArbolBinBusq * buscarNodoNoClaveArbolBinBusq(const ArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *))
{
    const ArbolBinBusq * busq = NULL;
    if (!*p)
        return NULL;
    if (cmp(&(*p)->info, d) < 0)
        return p;
    if ((busq = buscarNodoNoClaveArbolBinBusq(&(*p)->izq, busq, cmp)))
        return busq;
    return buscarNodoNoClaveArbolBinBusq(&(*p)->der, busq, cmp);
}

unsigned alturaArbolBin(const ArbolBinBusq * p)
{
    int hi, hd;
    if (!*p)
        return 0;
    hi = alturaArbolBin(&(*p)->izq);
    hd = alturaArbolBin(&(*p)->der);
    return (hi > hd ? hi : hd) + 1;
}

unsigned cantNodosArbolBin(const ArbolBinBusq * p)
{
    if (!*p)
        return 0;
    return cantNodosArbolBin(&(*p)->izq) + cantNodosArbolBin(&(*p)->der) + 1;
}

int mayorElemArbolBinBusq(const ArbolBinBusq * p, void * d, unsigned tam)
{
    if (!(p = mayorNodoArbolBinBusq(p)))
        return 0;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

int menorElemArbolBinBusq(const ArbolBinBusq * p, void * d, unsigned tam)
{
    if (!(p = menorNodoArbolBinBusq(p)))
        return 0;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

unsigned cantNodosHastaNivelArbolBin(const ArbolBinBusq *p, int n)
{
    if (!*p)
        return 0;

    if (n == 0)
        return 1;
    return cantNodosHastaNivelArbolBin(&(*p)->izq, n-1)
         + cantNodosHastaNivelArbolBin(&(*p)->der, n-1)
         + 1;
}

int esCompletoHastaNivelArbolBin(const ArbolBinBusq *p, int n)
{
    if (!*p)
        return n < 0;
    if (n == 0)
        return 1;
    return esCompletoHastaNivelArbolBin(&(*p)->izq, n-1) &&
           esCompletoHastaNivelArbolBin(&(*p)->der, n-1);
}

int esCompletoArbolBin(const ArbolBinBusq *p)
{
    return esCompletoHastaNivelArbolBin(p, alturaArbolBin(p) - 1);
}

int esBalanceadoArbolBin(const ArbolBinBusq *p)
{
    return esCompletoHastaNivelArbolBin(p, alturaArbolBin(p) - 2);
}

int esAVLArbolBin(const ArbolBinBusq *p)
{
    int hi, hd;
    if (!*p)
        return 1;
    hi = alturaArbolBin(&(*p)->izq);
    hd = alturaArbolBin(&(*p)->der);
    if (abs(hi - hd) > 1)
        return 0;
    return esAVLArbolBin(&(*p)->izq) && esAVLArbolBin(&(*p)->der);
}

int esCompleto2ArbolBin(const ArbolBinBusq *p)
{
    int h = alturaArbolBin(p);
    return cantNodosHastaNivelArbolBin(p, h) == pow(2, h) - 1;
}

int esBalanceado2ArbolBin(const ArbolBinBusq *p)
{
    int h = alturaArbolBin(p);
    return cantNodosHastaNivelArbolBin(p, h-2) == pow(2, h-1) - 1;
}

int esAVL2CalculoArbolBin(const ArbolBinBusq *p)
{
    int hi,
        hd;

    if(!*p)
        return 0;
    hi = esAVL2CalculoArbolBin(&(*p)->izq);
    hd = esAVL2CalculoArbolBin(&(*p)->der);
    if(hi < 0 || hd < 0 || abs(hi-hd) > 1)
        return -1;
    return (hi > hd ? hi : hd) + 1;
}

int esAVL2ArbolBin(const ArbolBinBusq *p)
{
    return esAVL2CalculoArbolBin(p) >= 0;
}



