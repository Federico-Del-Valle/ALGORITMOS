#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "tipos.h"


#define SIN_MEM         1
#define CLA_DUP         2
#define TODO_BIEN       0



void crearLista(tLista *p);
int  listaVacia(const tLista *p);
int  listaLlena(const tLista *p, unsigned cantBytes);
void vaciarLista(tLista *p);
int  ponerAlComienzo(tLista *p, const void *d, unsigned cantBytes);
int  sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes);
int  verPrimeroLista(const tLista *p, void *d, unsigned cantBytes);
int  ponerAlFinal(tLista *p, const void *d, unsigned cantBytes);
int  sacarUltimoLista(tLista *p, void *d, unsigned cantBytes);
int  verUltimoLista(const tLista *p, void *d, unsigned cantBytes);



int  vaciarListaYMostrar(tLista *p,
                         void (*mostrar)(const void *, FILE *), FILE *fp);

int  mostrarLista(const tLista *p,
                  void (*mostrar)(const void *, FILE *), FILE *fp);

int  mostrarListaAlReves(const tLista *p,
                         void (*mostrar)(const void *, FILE *), FILE *fp);

int  mostrarListaAlRevesYVaciar(tLista *p,
                                void (*mostrar)(const void *, FILE *),
                                FILE *fp);

int  ponerEnOrden(tLista *p, const void *d, unsigned cantBytes,
                  int (*comparar)(const void *, const void *),
                  int (*acumular)(void **, unsigned *, const void *, unsigned));

void ordenar(tLista *p, int (*comparar)(const void *, const void *));


#endif // LISTA_H_INCLUDED
