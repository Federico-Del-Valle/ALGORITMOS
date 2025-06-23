#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* izq;
    struct NodoArbol* der;
}NodoArbol;

typedef NodoArbol* Arbol;

void crearArbol(Arbol* a);
void vaciarArbol(Arbol* a);

int insertarArbol(Arbol* a, void* dato, unsigned tamDato, int(*Comparar)(const void*, const void*));



#endif // ARBOL_H_INCLUDED
