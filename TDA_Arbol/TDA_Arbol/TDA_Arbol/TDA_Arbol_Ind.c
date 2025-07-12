#include "TDA_Arbol_Ind.h"

void _guardarIndice(void *info, size_t tamInfo, size_t nivel, void *param)
{
    fwrite(info, tamInfo, 1, param);
}

/// ----------------------------------------
/// Busqueda en Indice
/// ----------------------------------------

int busqBinDesdeArchIndice(FILE *archInd, int clave, size_t *pos)
{
    if (!archInd)
        return ERR_ARCH;

    fseek(archInd, 0L, SEEK_END); // Mover al final para saber cuántos registros hay
    size_t total = ftell(archInd) / sizeof(tIndice);
    if (total == 0)
        return NO_ENCONTRADO;

    tIndice ind;
    size_t li = 0, ls = total - 1, medio;

    while (li <= ls)
    {
        medio = (li + ls) / 2;

        fseek(archInd, medio * sizeof(tIndice), SEEK_SET);
        fread(&ind, sizeof(tIndice), 1, archInd);

        if (ind.clave == clave)
        {
            *pos = ind.pos;
            return EXITO;
        }
        if (clave < ind.clave)
            ls = medio - 1;
        else
            li = medio + 1;
    }

    return NO_ENCONTRADO;
}

int busqBinArchIndice(char *nombArchInd, int clave, size_t *pos)
{
    FILE *arch = fopen(nombArchInd, "rb");
    if (!arch)
        return ERR_ARCH;

    int res = busqBinDesdeArchIndice(arch, clave, pos);
    fclose(arch);
    return res;
}

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

int crearDesdeArchBinIndice(FILE *archOri, FILE *archInd, size_t tamInfo,
                            int cmp(const void*, const void*),
                            int obtenerClave(void*),
                            int filter(void*, void*),
                            void *param)
{
    tArbol arbol;
    tIndice indice;
    void *buffer;
    size_t pos = 0;

    if (!archOri || !archInd)
        return ERR_ARCH;

    if (!(buffer = malloc(tamInfo)))
        return SIN_MEM;

    crearArbol(&arbol);

    while (fread(buffer, tamInfo, 1, archOri) == 1)
    {
        // Filtrar antes de agregar al índice
        if (!filter || filter(buffer, param) == 1)
        {
            indice.pos = pos;
            indice.clave = obtenerClave(buffer);

            if (rinsArb(&arbol, &indice, sizeof(tIndice), cmp) != EXITO)
            {
                free(buffer);
                eliminarArbol(&arbol);
                return ERR_INSER;
            }
        }
        pos++;
    }

    mapIn(&arbol, _guardarIndice, archInd);

    free(buffer);
    eliminarArbol(&arbol);
    return EXITO;
}

int crearArchBinIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo,
                       int cmp(const void*, const void*),
                       int obtenerClave(void*),
                       int filter(void*, void*),
                       void *param)
{
    FILE *archOri, *archInd;
    int res;

    if (!(archOri = fopen(nombArchOri, "rb")))
        return ERR_ARCH;

    if (!(archInd = fopen(nombArchInd, "wb")))
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    res = crearDesdeArchBinIndice(archOri, archInd, tamInfo, cmp, obtenerClave, filter, param);

    fclose(archOri);
    fclose(archInd);
    return res;
}

int mapDesdeArchBinIndice(FILE *archOri, FILE *archInd, size_t tamInfo, void accion(void*,void*), void *param)
{
    void *buffer;
    tIndice indice;

    if(!archOri || !archInd)
    {
        return ERR_ARCH;
    }

    if(!(buffer = malloc(tamInfo)))
    {
        return SIN_MEM;
    }

    rewind(archOri);
    rewind(archInd);

    while(fread(&indice, sizeof(indice), 1, archInd) == 1)
    {
        if(leerPosDesdeArchBin(archOri,buffer,tamInfo,indice.pos) == EXITO)
            accion(buffer, param);
    }

    free(buffer);
    return EXITO;
}
int mapArchBinIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo, void accion(void*,void*), void *param)
{
    FILE *archOri, *archInd;
    int res;

    if (!(archOri = fopen(nombArchOri, "rb")))
    {
        return ERR_ARCH;
    }

    if (!(archInd = fopen(nombArchInd, "rb")))
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    res = mapDesdeArchBinIndice(archOri, archInd, tamInfo, accion, param);

    fclose(archOri);
    fclose(archInd);
    return res;
}

int busqDesdeArchBinIndice(FILE *archOri, FILE *archInd, int clave, void *destino, size_t tamDes)
{
    if (!archOri || !archInd || !destino)
    {
        return ERR_ARCH;
    }

    size_t pos;
    int res;

    if ((res = busqBinDesdeArchIndice(archInd, clave, &pos)) != EXITO)
    {
        return res;
    }

    return leerPosDesdeArchBin(archOri, destino, tamDes, pos);
}
int busqArchBinIndice(char *nombArchOri, char *nombArchInd, int clave, void *destino, size_t tamDes)
{
    FILE *archOri, *archInd;

    if (!(archOri = fopen(nombArchOri, "rb")))
    {
        return ERR_ARCH;
    }

    if (!(archInd = fopen(nombArchInd, "rb")))
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    int res = busqDesdeArchBinIndice(archOri, archInd, clave, destino, tamDes);

    fclose(archOri);
    fclose(archInd);
    return res;
}

int modDesdeArchBinIndice(FILE *archOri, FILE *archInd, int clave, void *info, size_t tamInfo)
{
    if (!archOri || !archInd || !info)
    {
        return ERR_ARCH;
    }

    size_t pos;
    int res;

    if ((res = busqBinDesdeArchIndice(archInd, clave, &pos)) != EXITO)
    {
        return res;
    }

    fseek(archOri, pos * tamInfo, SEEK_SET);

    if (fwrite(info, tamInfo, 1, archOri) != 1)
        return ERR_ARCH;

    return EXITO;
}
int modArchBinIndice(char *nombArchOri, char *nombArchInd, int clave, void *info, size_t tamInfo)
{
    FILE *archOri, *archInd;

    if (!(archOri = fopen(nombArchOri, "rb+")))
    {
        return ERR_ARCH;
    }

    if (!(archInd = fopen(nombArchInd, "rb")))
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    int res = modDesdeArchBinIndice(archOri, archInd, clave, info, tamInfo);

    fclose(archOri);
    fclose(archInd);
    return res;
}

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

int crearDesdeArchTxtIndice(FILE *archOri, FILE *archInd, size_t tamInfo,
                            int cmp(const void*, const void*),
                            int obtenerClave(void *info),
                            int leerTrozado(char*, void*),
                            int filter(void*, void*), void *param)
{
    tArbol arbol;
    tIndice indice;
    void *buffer;
    char linea[BUFFER];
    size_t pos = 0;

    if (!archOri || !archInd)
        return ERR_ARCH;

    if (!(buffer = malloc(tamInfo)))
        return SIN_MEM;

    crearArbol(&arbol);

    while (fgets(linea, BUFFER, archOri) && leerTrozado(linea, buffer) == EXITO)
    {
        // Aplicar filtro si está definido
        if (!filter || filter(buffer, param) == 1)
        {
            indice.pos = pos;
            indice.clave = obtenerClave(buffer);

            if (rinsArb(&arbol, &indice, sizeof(tIndice), cmp) != EXITO)
            {
                free(buffer);
                eliminarArbol(&arbol);
                return ERR_INSER;
            }
        }

        pos++;
    }

    mapIn(&arbol, _guardarIndice, archInd);

    free(buffer);
    eliminarArbol(&arbol);
    return EXITO;
}
int crearArchTxtIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo,
                       int cmp(const void*, const void*),
                       int obtenerClave(void *info),
                       int leerTrozado(char*, void*),
                       int filter(void*, void*), void *param)
{
    FILE *archOri, *archInd;
    int res;

    if (!(archOri = fopen(nombArchOri, "rt")))
        return ERR_ARCH;

    if (!(archInd = fopen(nombArchInd, "wb")))
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    res = crearDesdeArchTxtIndice(archOri, archInd, tamInfo, cmp, obtenerClave, leerTrozado, filter, param);

    fclose(archOri);
    fclose(archInd);
    return res;
}

int mapDesdeArchTxtIndice(FILE *archOri, FILE *archInd, size_t tamInfo, void accion(void*,void*), void *param, int leerTrozado(char*, void*))
{
    void *buffer;
    char linea[BUFFER];
    tIndice indice;

    if(!archOri || !archInd)
    {
        return ERR_ARCH;
    }

    if(!(buffer = malloc(tamInfo)))
    {
        return SIN_MEM;
    }

    rewind(archOri);
    rewind(archInd);

    while(fread(&indice, sizeof(indice), 1, archInd) == 1)
    {
        if(leerPosDesdeArchBin(archOri,buffer,tamInfo,indice.pos) == EXITO)
        {
            leerTrozado(linea, buffer);
            accion(buffer, param);
        }
    }

    free(buffer);
    return EXITO;
}
int mapArchTxtIndice(char *nombArchOri, char *nombArchInd, size_t tamInfo, void accion(void*,void*), void *param, int leerTrozado(char*, void*))
{
    FILE *archOri, *archInd;
    int res;

    if (!(archOri = fopen(nombArchOri, "rb")))
    {
        return ERR_ARCH;
    }

    if (!(archInd = fopen(nombArchInd, "rb")))
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    res = mapDesdeArchTxtIndice(archOri, archInd, tamInfo, accion, param, leerTrozado);

    fclose(archOri);
    fclose(archInd);
    return res;
}

int busqDesdeArchTxtIndice(FILE *archOri, FILE *archInd, int clave, void *destino, size_t tamDes, int leerTrozado(char*, void*))
{
    if (!archOri || !archInd || !destino || !leerTrozado)
        return ERR_ARCH;

    size_t pos;
    int res = busqBinDesdeArchIndice(archInd, clave, &pos);
    if (res != EXITO)
        return res;

    char linea[BUFFER];
    size_t actual = 0;
    rewind(archOri);

    while (fgets(linea, sizeof(linea), archOri))
    {
        if (actual == pos)
            return leerTrozado(linea, destino);

        actual++;
    }

    return NO_ENCONTRADO;
}

int busqArchTxtIndice(char *nombArchOri, char *nombArchInd, int clave, void *destino, size_t tamDes, int leerTrozado(char*, void*))
{
    FILE *archOri = fopen(nombArchOri, "rt");
    if (!archOri)
        return ERR_ARCH;

    FILE *archInd = fopen(nombArchInd, "rb");
    if (!archInd)
    {
        fclose(archOri);
        return ERR_ARCH;
    }

    int res = busqDesdeArchTxtIndice(archOri, archInd, clave, destino, tamDes, leerTrozado);

    fclose(archOri);
    fclose(archInd);
    return res;
}

int modArchTxtIndice(char *nombArchOri, char *nombArchInd, int clave, void *nuevo, size_t tamInfo, int leerTrozado(char*, void*), int crearTrozado(char*, void*))
{
    FILE *archOri = fopen(nombArchOri, "rt");
    FILE *archInd = fopen(nombArchInd, "rb");
    FILE *archTmp = fopen("aux.txt", "wt");
    if (!archOri || !archInd || !archTmp)
    {
        if (archOri) fclose(archOri);
        if (archInd) fclose(archInd);
        if (archTmp) fclose(archTmp);
        return ERR_ARCH;
    }

    size_t pos, actual = 0;
    char linea[BUFFER];
    int res = busqBinDesdeArchIndice(archInd, clave, &pos);

    if (res != EXITO)
    {
        fclose(archOri);
        fclose(archInd);
        fclose(archTmp);
        return res;
    }

    while (fgets(linea, sizeof(linea), archOri))
    {
        if (actual == pos)
        {
            char nuevaLinea[BUFFER];
            crearTrozado(nuevaLinea, nuevo);
            fputs(nuevaLinea, archTmp);
        }
        else
        {
            fputs(linea, archTmp);
        }
        actual++;
    }

    fclose(archOri);
    fclose(archInd);
    fclose(archTmp);

    remove(nombArchOri);
    rename("aux.txt", nombArchOri);
    return EXITO;
}

/*
/// ----------------------------------------
/// Arbol
/// ----------------------------------------

void _guardarIndiceDesdeArbol(void *info, size_t tamInfo, size_t nivel, void *param)
{
    IndiceDesdeArbol *ctx = (IndiceDesdeArbol *)param;

    // Aplicar filtro si está definido
    if (!ctx->filter || ctx->filter(info, ctx->param))
    {
        tIndice indice;
        indice.clave = ctx->obtenerClave(info);
        indice.pos = ctx->pos;

        fwrite(&indice, sizeof(tIndice), 1, ctx->arch);
    }

    ctx->pos++;
}

int crearDesdeIndiceDesdeArbol(FILE *archInd, tArbol *arbol,
                               int (*obtenerClave)(void*),
                               int (*filter)(void*, void*),
                               void *param)
{
    if (!archInd)
        return ERR_ARCH;

    if (!*arbol)
        return ARBOL_VACIO;

    IndiceDesdeArbol ctx;
        ctx.arch = archInd;
        ctx.pos = 0;
        ctx.obtenerClave = obtenerClave;
        ctx.filter = filter;
        ctx.param = param;

    mapIn(arbol, _guardarIndiceDesdeArbol, &ctx);

    return EXITO;
}

int crearIndiceDesdeArbol(char *nombArchInd, tArbol *arbol,
                          int (*obtenerClave)(void*),
                          int (*filter)(void*, void*),
                          void *param)
{
    FILE *archInd;
    int res;

    if (!(archInd = fopen(nombArchInd, "wb")))
        return ERR_ARCH;

    res = crearDesdeIndiceDesdeArbol(archInd, arbol, obtenerClave, filter, param);

    fclose(archInd);
    return res;
}
*/

