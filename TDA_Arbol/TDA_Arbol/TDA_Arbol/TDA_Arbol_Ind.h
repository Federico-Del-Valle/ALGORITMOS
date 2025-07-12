/// =======================================================================================
/// @file TDA_Arbol_Ind.h
/// @brief Módulo para manejo de archivos con índice usando árboles binarios.
///
/// Este archivo permite crear, buscar, modificar y recorrer archivos utilizando un
/// archivo índice basado en claves enteras. Soporta tanto archivos binarios como de
/// texto, e incluye funciones auxiliares para vincular árboles binarios con índices.
/// =======================================================================================

#ifndef ARBOL_IND_H_INCLUDED
#define ARBOL_IND_H_INCLUDED

#include "TDA_Arbol_Arch.h"

/// ------------------------------------------------------------
/// Estructuras auxiliares
/// ------------------------------------------------------------

/// Nodo índice: clave asociada a posición del archivo original
typedef struct {
    int clave;
    size_t pos;
} tIndice;

/// Estructura auxiliar para recorrer árbol al generar archivo índice
typedef struct {
    FILE *arch;
    size_t pos;
    int (*obtenerClave)(void*);
    int (*filter)(void*, void*);
    void *param;
} IndiceDesdeArbol;

/// Escribe nodos índice al recorrer árbol (usado con mapIn)
void _guardarIndice(void *info, size_t tamInfo, size_t nivel, void *param);

/// ==========================================================================
/// Búsqueda con Índice
/// ==========================================================================

int busqBinDesdeArchIndice(FILE *archInd, int clave, size_t *pos); // Búsqueda binaria en archivo índice
int busqBinArchIndice(char *nombArchInd, int clave, size_t *pos);  // Igual que anterior pero con nombre

/// ==========================================================================
/// Archivos Binarios
/// ==========================================================================

int crearDesdeArchBinIndice(FILE *archOri, FILE *archInd, size_t tamInfo, int cmp(const void*, const void*), int obtenerClave(void*), int filter(void*, void*), void *param); // Crear índice desde binario abierto
int crearArchBinIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo, int cmp(const void*, const void*), int obtenerClave(void*), int filter(void*, void*), void *param); // Igual pero con nombres

int mapDesdeArchBinIndice(FILE *archOri, FILE *archInd, size_t tamInfo, void accion(void*,void*), void *param); // Aplicar función según índice
int mapArchBinIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo, void accion(void*,void*), void *param);

int busqDesdeArchBinIndice(FILE *archOri, FILE *archInd, int clave, void *destino, size_t tamDes); // Buscar elemento con índice
int busqArchBinIndice(char *nombArchOri, char *nombArchInd, int clave, void *destino, size_t tamDes);

int modDesdeArchBinIndice(FILE *archOri, FILE *archInd, int clave, void *info, size_t tamInfo); // Modificar por índice
int modArchBinIndice(char *nombArchOri, char *nombArchInd, int clave, void *info, size_t tamInfo);

/// ==========================================================================
/// Archivos Texto
/// ==========================================================================

int crearDesdeArchTxtIndice(FILE *archOri, FILE *archInd, size_t tamInfo, int cmp(const void*, const void*), int obtenerClave(void *info), int leerTrozado(char*, void*), int filter(void*, void*), void *param); // Crear índice desde texto abierto
int crearArchTxtIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo, int cmp(const void*, const void*), int obtenerClave(void *info), int leerTrozado(char*, void*), int filter(void*, void*), void *param); // Igual pero con nombres

int mapDesdeArchTxtIndice(FILE *archOri, FILE *archInd, size_t tamInfo, void accion(void*,void*), void *param, int leerTrozado(char*, void*)); // Recorrer por índice desde texto abierto
int mapArchTxtIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo, void accion(void*,void*), void *param, int leerTrozado(char*, void*));

int busqDesdeArchTxtIndice(FILE *archOri, FILE *archInd, int clave, void *destino, size_t tamDes, int leerTrozado(char*, void*)); // Buscar en texto con índice
int busqArchTxtIndice(char *nombArchOri, char *nombArchInd, int clave, void *destino, size_t tamDes, int leerTrozado(char*, void*));

int modArchTxtIndice(char *nombArchOri, char *nombArchInd, int clave, void *nuevo, size_t tamInfo, int leerTrozado(char*, void*), int crearTrozado(char*, void*)); // Modificar registro en archivo de texto

/// ==========================================================================
/// Árbol
/// ==========================================================================

/*
NO FUNCIONAN CORRECTAMENTE

void _guardarIndiceDesdeArbol(void *info, size_t tamInfo, size_t nivel, void *param); // Interna para mapIn
int crearDesdeIndiceDesdeArbol(FILE *archInd, tArbol *arbol, int (*obtenerClave)(void*), int (*filter)(void*, void*), void *param); // Árbol desde índice abierto
int crearIndiceDesdeArbol(char *nombArchInd, tArbol *arbol, int (*obtenerClave)(void*), int (*filter)(void*, void*), void *param); // Crear índice desde árbol
*/

#endif // ARBOL_IND_H_INCLUDED
