#ifndef INDICEABB_H_INCLUDED
#define INDICEABB_H_INCLUDED

int insertarIndice(tArbolBinBusq *arbol, int clave, long offset) ;



int insertarABB(tArbolBinBusq *pa, const void *dato, unsigned tamDato,
                int (*cmp)(const void *, const void *));

int buscarABB(tArbolBinBusq *pa, const void *dato, void **resultado,
              int (*cmp)(const void *, const void *));


void destruirABB(tArbolBinBusq *pa);

int guardarIndiceEnArchivo(FILE *f, tArbolBinBusq arbol);
int cargarIndiceDesdeArchivo(FILE *f, tArbolBinBusq *arbol, int (*cmp)(const void *, const void *));

int guardarABBConForma(FILE *f, tArbolBinBusq arbol);
int cargarABBConForma(FILE *f, tArbolBinBusq *arbol, unsigned tamDato,
                      int (*cmp)(const void *, const void *));
#endif // INDICEABB_H_INCLUDED
