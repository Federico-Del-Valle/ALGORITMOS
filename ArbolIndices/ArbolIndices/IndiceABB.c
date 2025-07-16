#include "datos.h"
#include "auxiliar.h"



int insertarIndice(tArbolBinBusq *arbol, int clave, long offset) {
    tIndice *nuevo = malloc(sizeof(tIndice));
    if (!nuevo)
        return 0;
    nuevo->clave = clave;
    nuevo->offset = offset;
    return insertarABB(arbol, nuevo, sizeof(tIndice), cmpIndice);
}


/** === Funciones auxiliares para el árbol === **/
int insertarABB(tArbolBinBusq *pa, const void *dato, unsigned tamDato,
                int (*cmp)(const void *, const void *)) {
    if (!*pa) {
        *pa = malloc(sizeof(tNodoArbol));
        if (!*pa)
            return 0;
        (*pa)->info = malloc(tamDato);
        if (!(*pa)->info) {
            free(*pa);
            return 0;
        }
        memcpy((*pa)->info, dato, tamDato);
        (*pa)->tamInfo = tamDato;
        (*pa)->izq = (*pa)->der = NULL;
        return 1;
    }

    int comp = cmp(dato, (*pa)->info);
    if (comp < 0)
        return insertarABB(&(*pa)->izq, dato, tamDato, cmp);
    if (comp > 0)
        return insertarABB(&(*pa)->der, dato, tamDato, cmp);

    // Clave duplicada
    return 0;
}

int buscarABB(tArbolBinBusq *pa, const void *dato, void **resultado,
              int (*cmp)(const void *, const void *)) {
    if (!*pa)
        return 0;

    int comp = cmp(dato, (*pa)->info);
    if (comp == 0) {
        *resultado = (*pa)->info;
        return 1;
    }

    if (comp < 0)
        return buscarABB(&(*pa)->izq, dato, resultado, cmp);
    else
        return buscarABB(&(*pa)->der, dato, resultado, cmp);
}

void destruirABB(tArbolBinBusq *pa) {
    if (!*pa)
        return;
    destruirABB(&(*pa)->izq);
    destruirABB(&(*pa)->der);
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}


int guardarIndiceEnArchivo(FILE *f, tArbolBinBusq arbol) {
    if (!arbol)
        return 1; // Nada que guardar

    // Escribir la info del nodo
    if (fwrite(arbol->info, arbol->tamInfo, 1, f) != 1)
        return 0;

    // Recorrer hijos en preorden
    if (!guardarIndiceEnArchivo(f, arbol->izq))
        return 0;
    if (!guardarIndiceEnArchivo(f, arbol->der))
        return 0;

    return 1;
}


int cargarIndiceDesdeArchivo(FILE *f, tArbolBinBusq *arbol, int (*cmp)(const void *, const void *)) {
    tIndice indice;
    while (fread(&indice, sizeof(tIndice), 1, f) == 1) {
        if (!insertarABB(arbol, &indice, sizeof(tIndice), cmp))
            return 0;
    }
    return 1;
}




int guardarABBConForma(FILE *f, tArbolBinBusq arbol) {
    if (!f)
        return 0;

    if (arbol == NULL) {
        unsigned char flag = 0;
        fwrite(&flag, sizeof(flag), 1, f);
        return 1;
    }

    unsigned char flag = 1;
    if (fwrite(&flag, sizeof(flag), 1, f) != 1)
        return 0;

    // Guardar el contenido del nodo
    if (fwrite(arbol->info, arbol->tamInfo, 1, f) != 1)
        return 0;

    // Guardar hijos
    if (!guardarABBConForma(f, arbol->izq))
        return 0;
    if (!guardarABBConForma(f, arbol->der))
        return 0;

    return 1;
}


int cargarABBConForma(FILE *f, tArbolBinBusq *arbol, unsigned tamDato,
                      int (*cmp)(const void *, const void *)) {
    if (!f)
        return 0;

    unsigned char flag;
    if (fread(&flag, sizeof(flag), 1, f) != 1)
        return 0;

    if (flag == 0) {
        *arbol = NULL;
        return 1;
    }

    void *dato = malloc(tamDato);
    if (!dato)
        return 0;

    if (fread(dato, tamDato, 1, f) != 1) {
        free(dato);
        return 0;
    }

    // Insertar nodo
    *arbol = malloc(sizeof(tNodoArbol));
    if (!*arbol) {
        free(dato);
        return 0;
    }

    (*arbol)->info = dato;
    (*arbol)->tamInfo = tamDato;
    (*arbol)->izq = (*arbol)->der = NULL;

    if (!cargarABBConForma(f, &(*arbol)->izq, tamDato, cmp) ||
        !cargarABBConForma(f, &(*arbol)->der, tamDato, cmp)) {
        destruirABB(arbol); // limpiar en caso de error
        return 0;
    }

    return 1;
}



