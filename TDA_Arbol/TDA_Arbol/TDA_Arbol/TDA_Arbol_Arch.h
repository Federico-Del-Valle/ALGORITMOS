/// =======================================================================================
/// @file TDA_Arbol_Arch.h
/// @brief Funciones para interacción entre árboles binarios y archivos (texto y binario).
///
/// Permite cargar árboles desde archivos con datos ordenados o desordenados, y guardar
/// árboles en archivos. Se trabaja tanto con archivos binarios como de texto, y se
/// pueden aplicar funciones de filtrado o trozado para manipular los datos.
/// =======================================================================================

#ifndef TDA_ARBOL_ARCH_H_INCLUDED
#define TDA_ARBOL_ARCH_H_INCLUDED

#include "archs_gen.h"
#include "TDA_Arbol.h"

/// ==========================================================================
/// Funciones de árbol con archivo desordenado
/// ==========================================================================

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

/// Carga árbol desde archivo binario abierto, con datos desordenados
int cargarDesdeArchBinDesArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int (*filter)(void*, void*), void *param);

/// Igual que anterior, pero abriendo el archivo por nombre
int cargarArchBinDesArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int (*filter)(void*, void*), void *param);

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

/// Carga árbol desde archivo de texto abierto, con datos desordenados
int cargarDesdeArchTxtDesArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param);

/// Igual que anterior, pero abriendo el archivo por nombre
int cargarArchTxtDesArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param);


/// ==========================================================================
/// Funciones de árbol con archivo ordenado
/// ==========================================================================

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

/// Función auxiliar recursiva para cargar árbol balanceado desde binario
int _cargarDesdeArchBinOrdArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int li, int ls, int (*filter)(void*, void*), void *param);

/// Carga árbol balanceado desde archivo binario abierto
int cargarDesdeArchBinOrdArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int (*filter)(void*, void*), void *param);

/// Igual que anterior, pero abriendo el archivo por nombre
int cargarArchBinOrdArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int (*filter)(void*, void*), void *param);

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

/// Función auxiliar recursiva para cargar árbol balanceado desde texto
int _cargarDesdeArchTxtOrdArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int leerTrozado(char*, void*), int li, int ls, int (*filter)(void*, void*), void *param);

/// Carga árbol balanceado desde archivo de texto abierto
int cargarDesdeArchTxtOrdArbol(FILE *arch, tArbol *arbol , size_t tamInfo, int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param);

/// Igual que anterior, pero abriendo el archivo por nombre
int cargarArchTxtOrdArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param);


/// ==========================================================================
/// Funciones de Arboles con Archivos
/// ==========================================================================

/// Crea archivo binario desde el contenido del árbol (recorrido inorden)
int crearArchBinArbol(char *nombArch, tArbol *arbol, size_t taminfo);

/// Crea archivo de texto desde árbol, usando función `crearTrozado`
int crearArchTxtArbol(char *nombArch, tArbol *arbol, size_t taminfo, int crearTrozado(char*, void*));

#endif // TDA_ARBOL_ARCH_H_INCLUDED
