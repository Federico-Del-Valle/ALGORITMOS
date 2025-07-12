#include "archs_gen.h"

/// ----------------------------------------
/// Archivos Binarios
/// ----------------------------------------

int crearArchBin(char *nombArch, void *vec, size_t lon, size_t tamEl)
{
    FILE *arch;

    if(!(arch = fopen(nombArch, "wb")))
    {
        return ERR_ARCH;
    }

    fwrite(vec, tamEl, lon, arch);

    fclose(arch);
    return EXITO;
}
int leerDesdeArchBin(FILE *arch, size_t tamInfo , void accion(void*,void*), void *param)
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

    while(fread(buffer,tamInfo, 1, arch) == 1)
    {
        accion(buffer, param);
    }

    free(buffer);
    return EXITO;
}
int leerArchBin(char *nombArch, size_t tamInfo , void accion(void*,void*), void *param)
{
    FILE *arch;
    int res;

    if(!(arch = fopen(nombArch,"rb")))
    {
        return ERR_ARCH;
    }

    res = leerDesdeArchBin(arch,tamInfo,accion,param);

    fclose(arch);
    return res;
}

int leerPosDesdeArchBin(FILE *arch, void *destino, size_t tamDes, size_t pos)
{
    if (!arch || !destino)
    {
        return ERR_ARCH;
    }

    fseek(arch, pos * tamDes, SEEK_SET);

    if (fread(destino, tamDes, 1, arch) != 1)
        return POS_INV;

    return EXITO;
}
int leerPosArchBin(char *nombArch, void *destino, size_t tamDes, size_t pos)
{
    FILE *arch;

    if (!(arch = fopen(nombArch, "rb")))
    {
        return ERR_ARCH;
    }

    int res = leerPosDesdeArchBin(arch, destino, tamDes, pos);

    fclose(arch);
    return res;
}

/// ----------------------------------------
/// Archivos Texto
/// ----------------------------------------

int crearArchTxt(char *nombArch, void *vec, size_t lon, size_t tamEl, int crearTrozado(char*, void*))
{
    FILE *arch;
    char linea[BUFFER];

    void *fin = vec + lon * tamEl;

    if(!(arch = fopen(nombArch, "wt")))
    {
        return ERR_ARCH;
    }

    while(vec < fin)
    {
        crearTrozado(linea, vec);
        fputs(linea, arch);
        vec += tamEl;
    }

    fclose(arch);
    return EXITO;
}
int leerDesdeArchTxt(FILE *arch, size_t tamInfo, int leerTrozado(char*, void*), void accion(void*,void*), void *param)
{
    char linea[BUFFER];
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
    while(fgets(linea,BUFFER,arch) && leerTrozado(linea, buffer) == EXITO)
    {
        accion(buffer, param);
    }

    free(buffer);
    return EXITO;
}
int leerArchTxt(char *nombArch, size_t tamInfo, int leerTrozado(char*, void*), void accion(void*,void*), void *param)
{
    FILE *arch;
    int res;

    if(!(arch = fopen(nombArch, "rt")))
    {
        return ERR_ARCH;
    }

    res = leerDesdeArchTxt(arch,tamInfo,leerTrozado,accion,param);

    fclose(arch);
    return res;
}

int leerPosDesdeArchTxt(FILE *arch, void *destino, size_t tamDes, size_t pos, int leerTrozado(char*, void*))
{
    if (!arch || !destino)
    {
        return ERR_ARCH;
    }

    char linea[BUFFER];
    size_t cont = 0;

    rewind(arch);

    // Avanzar hasta la línea deseada
    while (fgets(linea, sizeof(linea), arch))
    {
        if (cont == pos)
        {
            leerTrozado(linea, destino);
            return EXITO;
        }
        cont++;
    }

    return POS_INV;  // No se encontró la línea
}
int leerPosArchTxt(char *nombArch, void *destino, size_t tamDes, size_t pos, int leerTrozado(char*, void*))
{
    FILE *arch;

    if (!(arch = fopen(nombArch, "rt")))
    {
        return ERR_ARCH;
    }

    int res = leerPosDesdeArchTxt(arch, destino, tamDes, pos, leerTrozado);

    fclose(arch);
    return res;
}
