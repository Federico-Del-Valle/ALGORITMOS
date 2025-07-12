/// =======================================================================================
/// @file arbol.h
/// @brief Definición y operaciones sobre Árboles Binarios Generales en C.
///
/// Este archivo define un TDA Árbol Binario con múltiples variantes de inserción,
/// recorridos, operaciones de búsqueda, conteo, análisis estructural (AVL, balanceado, completo), y eliminación de nodos.
/// =======================================================================================

#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// Códigos de retorno
#define EXITO            1
#define SIN_MEM         -4
#define DUPLICADO       -3
#define NO_ES_HOJA      -2
#define NO_ENCONTRADO   -1
#define ERR_INSER       -6
#define ARBOL_VACIO      0

#define MIN(X,Y) ((X) > (Y) ? (Y) : (X))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

/// Estructura del nodo del árbol
typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

/// Tipos de funciones auxiliares
typedef int (*comparar)(const void* a, const void* b);
typedef void (*procesar)(const void* a);

/// ------------------------------------------------------------
/// Inicialización
/// ------------------------------------------------------------
void crearArbol(tArbol* arbol); // Inicializa el árbol como vacío

/// ------------------------------------------------------------
/// Insertar
/// ------------------------------------------------------------
int insArb(tArbol *arbol, void *info, size_t tamInfo, comparar cmp);      // Inserción estándar
int rinsArb(tArbol *arbol, void *info, size_t tamInfo, comparar cmp);     // Inserción recursiva
int insDirArb(tArbol *arbol, void *info, size_t tamInfo, comparar cmp);   // Inserción directa (sin verificar)

/// ------------------------------------------------------------
/// Recorridos
/// ------------------------------------------------------------
void mapPre(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param);       // Pre-orden
void _mapPre(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel);

void mapIn(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param);        // In-orden
void _mapIn(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel);

void mapPos(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param);       // Pos-orden
void _mapPos(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel);

void mapPreInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param);    // Pre-orden inverso
void _mapPreInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel);

void mapInInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param);     // In-orden inverso
void _mapInInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel);

void mapPosInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param);    // Pos-orden inverso
void _mapPosInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel);

/// ------------------------------------------------------------
/// Estadísticas del Árbol
/// ------------------------------------------------------------
size_t alturaArbol(tArbol *arbol);                        // Altura del árbol
int esCompletoHastaNivelArbol(tArbol *arbol, size_t n);   // ¿Completo hasta nivel n?
int esCompletoArbol(tArbol *arbol);                       // ¿Es completo?

int esBalanceadoArbol(tArbol *arbol);                     // ¿Balanceado?
int esBalanceado2Arbol(tArbol *arbol);                    // Variante balanceada

int esAVLArbol(tArbol *arbol);                            // ¿Cumple propiedad AVL?

/// ------------------------------------------------------------
/// Estadísticas de los Nodos
/// ------------------------------------------------------------
size_t cantNodosArbol(tArbol *arbol);                     // Total de nodos
size_t cantHojasArbol(tArbol* arbol);                     // Nodos hoja
size_t cantNoHojasArbol(tArbol* arbol);                   // Nodos no hoja

size_t cantNodosHastaNivel(tArbol* arbol,size_t nivel);   // Nodos hasta nivel
size_t cantNodosEnNivel(tArbol* arbol,size_t nivel);      // Nodos en nivel exacto
size_t _cantNodosEnNivel(tArbol* arbol,size_t nivelActual, size_t nivelObjetivo);
size_t cantNodosAPartirDeNivel(tArbol* arbol,size_t nivel);
size_t _cantNodosAPartirDeNivel(tArbol* arbol,size_t nivelActual, size_t nivelObjetivo);

size_t cantNodosSubArbol(tArbol* arbol, void* clave, comparar cmp);  // Nodos del subárbol con raíz dada

size_t cantHijosIzq(tArbol* arbol);              // Nodos con hijo izquierdo
size_t cantHijosSoloIzq(tArbol* arbol);          // Nodos con solo hijo izquierdo

/// ------------------------------------------------------------
/// Búsqueda
/// ------------------------------------------------------------
tArbol* busqNodoArbol(tArbol* arbol, void* clave, comparar cmp);            // Buscar nodo
int busqElemArbol(tArbol* arbol, void* destino, size_t tamDestino, comparar cmp);  // Buscar elemento

/// ------------------------------------------------------------
/// Mínimos y Máximos
/// ------------------------------------------------------------
tArbol* busqNodoMaxArbol(tArbol *arbol);                             // Nodo con valor máximo
tArbol* busqNodoMinArbol(tArbol *arbol);                             // Nodo con valor mínimo
int busqElemMaxArbol(tArbol *arbol, void *info, size_t tamInfo);     // Elemento máximo
int busqElemMinArbol(tArbol *arbol, void *info, size_t tamInfo);     // Elemento mínimo

/// ------------------------------------------------------------
/// Eliminación
/// ------------------------------------------------------------
int eliminarHoja(tArbol* arbol, void* claveHoja, comparar cmp);  // Eliminar hoja específica
int eliminarRaiz(tArbol* arbol);                                 // Eliminar raíz
int eliminarNodo(tArbol* arbol, void* clave, comparar cmp);      // Eliminar nodo cualquiera

/// ------------------------------------------------------------
/// Limpieza
/// ------------------------------------------------------------
void eliminarArbol(tArbol* arbol);  // Libera todo el árbol

/// ------------------------------------------------------------
/// Operaciones sin clave
/// ------------------------------------------------------------
tArbol* busqNodoMinNoClaveArbol(tArbol *arbol, comparar cmp);
tArbol* _busqNodoMinNoClaveArbol(tArbol *arbol, tArbol *min, comparar cmp);
int busqElemMinNoClaveArbol(tArbol *arbol, void *info, size_t tamInfo, comparar cmp);

tArbol* busqNodoMaxNoClaveArbol(tArbol *arbol, comparar cmp);
tArbol* _busqNodoMaxNoClaveArbol(tArbol *arbol, tArbol *max, comparar cmp);
int busqElemMaxNoClaveArbol(tArbol *arbol, void *info, size_t tamInfo, comparar cmp);

tArbol* busqNodoNoClaveArbol(tArbol* arbol, void* info, comparar cmp);              // Buscar nodo sin clave directa
int busqElemNoClaveArbol(tArbol* arbol, void* destino, size_t tamDestino, comparar cmp); // Buscar elemento sin clave

void eliminarNodoNoClaveArbol(tArbol *arbol, void *info, comparar cmp); // Eliminar sin clave directa

#endif // ARBOL_H_INCLUDED
