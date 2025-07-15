#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

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
void insertarEnArbol(Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));
void recorrerArbol(Arbol*,unsigned, void* params, void(*accion)(void*, unsigned, unsigned));
int buscarElemArbol(Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));



#endif // ARBOL_H_INCLUDED
