#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#define MINIMO(x,y) ((x) < (y) ? (x) : (y))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nodoArbol
{
    void* info;
    unsigned tamInfo;
    struct nodoArbol* izq;
    struct nodoArbol* der;
}nodoArbol;

typedef nodoArbol* Arbol;

typedef struct
{
    int nroReg;
    int idProducto;
}indice;

void iniciarArbol(Arbol*);
int insertarEnArbol(Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));
void recorrerArbol(Arbol*,unsigned, void* , void(*accion)(void*, unsigned, unsigned, void*));
int buscarElemArbol(Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));
nodoArbol** buscarNodo(Arbol*, const void* , int(*cmp)(const void*, const void*));
int eliminarRaiz(Arbol*);
int eliminarElem(Arbol*, void*, unsigned tam, int(*cmp)(const void*, const void*));
int esAVL(const Arbol*);
int esCompleto(const Arbol*);
int esCompletoHataNivel(const Arbol*, int );
nodoArbol** mayorNodo(const Arbol*);
nodoArbol** menorNodo(const Arbol* );


#endif // ARBOL_H_INCLUDED
