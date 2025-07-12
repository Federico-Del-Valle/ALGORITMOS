/// =======================================================================================
/// @file utilidades.h
/// @brief Funciones auxiliares para pruebas, comparaciones, filtros y visualización.
///
/// Este módulo contiene funciones de comparación, mapeo, filtrado, y visualización para
/// tipos de datos genéricos como `int` y estructuras como `tPrueba`, usadas en el manejo
/// de árboles y archivos con índice.
/// =======================================================================================

#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include "TDA_Arbol/TDA_Arbol_Ind.h"

#define TAMDESC     10  // Tamaño de descripción en tPrueba

/// ------------------------------------------------------------
/// Funciones para `int`
/// ------------------------------------------------------------
int cmpInt(const void* a, const void* b);                                  // Comparar enteros
void mostrarInt(const void* info);                                         // Mostrar entero
void mostrarIntMap(void *info, size_t tamInfo, size_t nivel, void *param); // Mostrar entero con nivel (map)

/// ------------------------------------------------------------
/// Funciones para `tPrueba`
/// ------------------------------------------------------------

typedef struct {
    int clave;
    char descrip[TAMDESC];
    int cant;
} tPrueba;

int generarLotePrueba(char *nombArch);   // Genera lote de pruebas

void mostrarPruebaCabe();                                                     // Mostrar cabecera de la estructura
void mostrarPrueba(void *info, void *param);                                 // Mostrar tPrueba simple
void mostrarPruebaClave(void *info, void *param);                             // Mostrar solo clave
void mostrarPruebaMap(void *info, size_t tamInfo, size_t nivel, void *param); // Mostrar en map

int cmpPrueba(const void* a, const void* b);                      // Comparar tPrueba por clave
int obtenerClavePrueba(void *info);                               // Obtener clave de tPrueba
int filterMenor(void *info, void *param);                         // Filtro por menor a un valor

/// ------------------------------------------------------------
/// Funciones para Índices
/// ------------------------------------------------------------
void mostrarIndiceCabe();                    // Mostrar cabecera de la estructura
void mostrarIndice(void *info, void *param); // Mostrar estructura índice

#endif // UTILIDADES_H_INCLUDED
