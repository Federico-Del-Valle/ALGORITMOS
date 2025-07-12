#include "TDA_Arbol_Arch.h"

/// ==========================================================================
/// Funciones de arbol con archivo desordenado
/// ==========================================================================

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

int cargarDesdeArchBinDesArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int (*filter)(void*, void*), void *param)
{
    void *buffer;

    if(!arch)
    {
        return ERR_ARCH;
    }

    if(!(buffer = malloc(tamInfo)))
    {
        return SIN_MEM;
    }

    rewind(arch);

    while(fread(buffer, tamInfo, 1, arch) == 1)
    {
        // Si no hay filtro o se cumple la condición, insertar
        if (!filter || filter(buffer, param))
            insArb(arbol, buffer, tamInfo, cmp);
    }

    return EXITO;
}

int cargarArchBinDesArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int (*filter)(void*, void*), void *param)
{
    FILE *arch;
    int res;

    if(!(arch = fopen(nombArch,"rb")))
    {
        return ERR_ARCH;
    }

    res = cargarDesdeArchBinDesArbol(arch,arbol,tamInfo,cmp,filter,param);

    fclose(arch);
    return res;
}

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

int cargarDesdeArchTxtDesArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param)
{
    void *buffer;
    char linea[BUFFER];

    if(!arch)
    {
        return ERR_ARCH;
    }

    if(!(buffer = malloc(tamInfo)))
    {
        return SIN_MEM;
    }

    while(fgets(linea, BUFFER, arch) && leerTrozado(linea, buffer) == EXITO)
    {
        // Si no hay filtro o se cumple la condición
        if (!filter || filter(buffer, param))
            insArb(arbol, buffer, tamInfo, cmp);
    }

    free(buffer);
    return EXITO;
}

int cargarArchTxtDesArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int cmp(const void*, const void*), int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param)
{
    FILE *arch;
    int res;

    if(!(arch = fopen(nombArch,"rt")))
    {
        return ERR_ARCH;
    }

    res = cargarDesdeArchTxtDesArbol(arch,arbol,tamInfo,cmp,leerTrozado, filter, param);

    fclose(arch);
    return res;
}

/// ==========================================================================
/// Funciones de arbol con archivo Ordenado
/// ==========================================================================

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

/*
* - Usa una estrategia de división por mitades (tipo árbol completo balanceado).
* - Elige el elemento del medio (m) como raíz.
* - Repite recursivamente con los tramos izquierdo y derecho para formar subárboles.
*/
int _cargarDesdeArchBinOrdArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int li, int ls, int (*filter)(void*, void*), void *param)
{
    if (li > ls)
        return EXITO;

    int m = (li + ls) / 2;
    void *buffer = malloc(tamInfo);
    if (!buffer)
        return SIN_MEM;

    // Leer el elemento en la posición m
    fseek(arch, m * tamInfo, SEEK_SET);
    if (fread(buffer, tamInfo, 1, arch) != 1)
    {
        free(buffer);
        return ERR_ARCH;
    }

    // Aplicar filtro: si no pasa el filtro, seguir con recursión sin insertarlo
    int resIzq = _cargarDesdeArchBinOrdArbol(arch, arbol, tamInfo, li, m - 1, filter, param);

    if (!filter || filter(buffer, param)) // Si no hay filtro, lo acepta
    {
        *arbol = malloc(sizeof(tNodo));
        if (!*arbol)
        {
            free(buffer);
            return SIN_MEM;
        }

        (*arbol)->info = buffer;
        (*arbol)->tamInfo = tamInfo;
        (*arbol)->izq = NULL;
        (*arbol)->der = NULL;

        int resDer = _cargarDesdeArchBinOrdArbol(arch, &(*arbol)->der, tamInfo, m + 1, ls, filter, param);
        return resDer;
    }
    else
    {
        free(buffer);
        // Si no insertamos en el nodo actual, seguimos en ambos lados (por separado)
        int resDer = _cargarDesdeArchBinOrdArbol(arch, arbol, tamInfo, m + 1, ls, filter, param);
        return resIzq != EXITO ? resIzq : resDer;
    }
}
int cargarDesdeArchBinOrdArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int (*filter)(void*, void*), void *param)
{
    fseek(arch, 0L, SEEK_END);
    return _cargarDesdeArchBinOrdArbol(arch, arbol, tamInfo, 0, ftell(arch) / tamInfo - 1, filter, param);
}
int cargarArchBinOrdArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int (*filter)(void*, void*), void *param)
{
    int  res;
    FILE *arch;

    if (*arbol)
    {
        return 0;
    }

    if (!(arch = fopen(nombArch, "rb")))
    {
        return ERR_ARCH;
    }

    res = cargarDesdeArchBinOrdArbol(arch, arbol, tamInfo, filter, param);

    fclose(arch);
    return res;
}

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

int _cargarDesdeArchTxtOrdArbol(FILE *arch, tArbol *arbol, size_t tamInfo, int leerTrozado(char*, void*), int li, int ls, int (*filter)(void*, void*), void *param)
{
    if (li > ls)
        return EXITO;

    int m = (li + ls) / 2;
    char linea[BUFFER];
    void *buffer = malloc(tamInfo);
    if (!buffer)
        return SIN_MEM;

    // Ir a la línea m
    fseek(arch, 0L, SEEK_SET);
    for (int i = 0; i <= m; i++) {
        if (!fgets(linea, BUFFER, arch)) {
            free(buffer);
            return ERR_ARCH;
        }
    }

    if (leerTrozado(linea, buffer) != EXITO) {
        free(buffer);
        return ERR_ARCH;
    }

    // Recursión izquierda
    int resIzq = _cargarDesdeArchTxtOrdArbol(arch, arbol, tamInfo, leerTrozado, li, m - 1, filter, param);

    // Verifica si pasa el filtro
    if (!filter || filter(buffer, param)) {
        *arbol = malloc(sizeof(tNodo));
        if (!*arbol) {
            free(buffer);
            return SIN_MEM;
        }

        (*arbol)->info = buffer;
        (*arbol)->tamInfo = tamInfo;
        (*arbol)->izq = NULL;
        (*arbol)->der = NULL;

        // Recursión derecha
        int resDer = _cargarDesdeArchTxtOrdArbol(arch, &(*arbol)->der, tamInfo, leerTrozado, m + 1, ls, filter, param);
        return resDer;
    } else {
        free(buffer);
        int resDer = _cargarDesdeArchTxtOrdArbol(arch, arbol, tamInfo, leerTrozado, m + 1, ls, filter, param);
        return resIzq != EXITO ? resIzq : resDer;
    }
}
int cargarDesdeArchTxtOrdArbol(FILE *arch, tArbol *arbol , size_t tamInfo, int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param)
{
    fseek(arch, 0L, SEEK_SET);
    int cantReg = 0;
    char aux[BUFFER];

    while (fgets(aux, BUFFER, arch))
    {
        cantReg++;
    }

    rewind(arch);

    return _cargarDesdeArchTxtOrdArbol(arch, arbol, tamInfo, leerTrozado, 0, cantReg - 1, filter, param);
}
int cargarArchTxtOrdArbol(char *nombArch, tArbol *arbol, size_t tamInfo, int leerTrozado(char*, void*), int (*filter)(void*, void*), void *param)
{
    int  res;
    FILE *arch;

    if (*arbol)
    {
        return 0;
    }

    if (!(arch = fopen(nombArch, "rt")))
    {
        return ERR_ARCH;
    }

    res = cargarDesdeArchTxtOrdArbol(arch, arbol, tamInfo, leerTrozado, filter, param);

    fclose(arch);
    return res;
}

/// ==========================================================================
/// Funciones de Arboles con Archivos
/// ==========================================================================+

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

void _crearArchBinArbol(void *info, size_t tamInfo, size_t nivel, void *param)
{
    fwrite(info,tamInfo,1,param);
}
int crearArchBinArbol(char *nombArch, tArbol *arbol, size_t taminfo)
{
    FILE *arch;

    if(!(arch = fopen(nombArch, "wb")))
    {
        return ERR_ARCH;
    }

    mapIn(arbol,_crearArchBinArbol,arch);

    fclose(arch);
    return EXITO;
}

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

void _crearArchTxtArbol(void *info, size_t tamInfo, size_t nivel, void *param)
{
    void** contexto = (void**)param;

    FILE* arch = (FILE*)contexto[0];
    int (*crearTrozado)(char*, void*) = (int (*)(char*, void*))contexto[1];

    char linea[256];
    crearTrozado(linea, info);
    fputs(linea, arch);
}
int crearArchTxtArbol(char *nombArch, tArbol *arbol, size_t taminfo, int crearTrozado(char*, void*))
{
    FILE *arch;

    if(!(arch = fopen(nombArch,"wt")))
    {
        return ERR_ARCH;
    }

    void *contx[] = { arch, crearTrozado };
    mapIn(arbol, _crearArchTxtArbol, contx);

    fclose(arch);
    return EXITO;
}
