/// =======================================================================================
/// @file archs_gen.h
/// @brief Funciones genéricas para trabajar con archivos binarios y de texto.
///
/// Provee operaciones para crear archivos a partir de vectores en memoria, leerlos
/// secuencialmente o por posición, y aplicar funciones a cada elemento.
/// =======================================================================================

#ifndef ARCHS_H_INCLUDED
#define ARCHS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archs_gen.h"

#define ERR_ARCH -1   // Error al abrir archivo
#define POS_INV  -3   // Posición inválida
#define SIN_MEM  -2   // Falta de memoria
#define EXITO     1   // Éxito

#define BUFFER   256  // Tamaño del buffer de texto

/// =====================================================================================================
/// Archivos Binarios
/// =====================================================================================================

/// Crea un archivo binario desde un vector
int crearArchBin(char *nombArch, void *vec, size_t lon, size_t tamEl);


/// Lee un archivo binario abierto y aplica una acción
int leerDesdeArchBin(FILE *arch, size_t tamInfo , void accion(void*,void*), void *param);

/// Igual que anterior, pero abriendo el archivo por nombre
int leerArchBin(char *nombArch, size_t tamInfo , void accion(void*,void*), void *param);


/// Lee un elemento en una posición desde archivo binario abierto
int leerPosDesdeArchBin(FILE *arch, void *destino, size_t tamDes, size_t pos);

/// Igual que anterior, pero abriendo el archivo por nombre
int leerPosArchBin(char *nombArch, void *destino, size_t tamDes, size_t pos);


/// =====================================================================================================
/// Archivos Texto
/// =====================================================================================================

/// Crea un archivo de texto desde un vector (usando función trozadora)
int crearArchTxt(char *nombArch, void *vec, size_t lon, size_t tamEl, int crearTrozado(char*, void*));


/// Lee un archivo de texto abierto, troza y aplica una acción
int leerDesdeArchTxt(FILE *arch, size_t tamInfo, int leerTrozado(char*, void*), void accion(void*,void*), void *param);

/// Igual que anterior, pero abriendo el archivo por nombre
int leerArchTxt(char *nombArch, size_t tamInfo, int leerTrozado(char*, void*), void accion(void*,void*), void *param);


/// Lee una posición específica de archivo de texto abierto
int leerPosDesdeArchTxt(FILE *arch, void *destino, size_t tamDes, size_t pos, int leerTrozado(char*, void*));

/// Igual que anterior, pero abriendo el archivo por nombre
int leerPosArchTxt(char *nombArch, void *destino, size_t tamDes, size_t pos, int leerTrozado(char*, void*));

#endif // ARCHS_H_INCLUDED
