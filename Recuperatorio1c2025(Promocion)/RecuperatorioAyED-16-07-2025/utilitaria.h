#ifndef UTILITARIA_H_INCLUDED
#define UTILITARIA_H_INCLUDED
#include "tipos.h"
#include "arbol_bin_busq.h"
void abrirYMostrarPacientes();
void abrirYMostrar10Pacientes();

typedef struct
{
    int nroReg;
    int nroPaciente;
}Indice;

typedef struct
{
    int nroPaciente;
    float monto;
}Consulta;


int cargarArbolIdx(tArbolBinBusq* p, char nombre[]);
int darDeBaja(tArbolBinBusq*, int, FILE* );
int darAlta(tArbolBinBusq*, FILE*);
int generarConsulta(tArbolBinBusq* p, FILE* arch);



//Funciones mias arboles
tNodoArbol** mayorNodo(tArbolBinBusq* p);
tNodoArbol** menorNodo(tArbolBinBusq* p);
int eliminarRaiz(tArbolBinBusq* p);
tNodoArbol** buscarNodo(tArbolBinBusq* p, const void* d, int(*cmp)(const void*, const void*));
int buscarElem( tArbolBinBusq* p, void* d, unsigned tam, int(*cmp)(const void*, const void*));
int eliminarElem(tArbolBinBusq* p, void* d, unsigned tam, int(*cmp)(const void*, const void*));
int alturaArbol( tArbolBinBusq* p);
int insertarArbol(tArbolBinBusq *p, const void* d, unsigned tam, int(*cmp)(const void *, const void *));

//funciones mias cola


void crearColaMia(tCola* p);
int ponerEnColaMia(tCola* p, const void* d, unsigned cantBytes);
int sacarDeColaMia(tCola* p, void* d, unsigned cantBytes);




#endif // UTILITARIA_H_INCLUDED
