#include "utilidades.h"

/// ==================================================================
/// Funciones de Int
/// ==================================================================
int cmpInt(const void* a, const void* b)
{
    return *(int*)a-*(int*)b;
}
void mostrarInt(const void*info)
{
    printf("%d ", *(int*)info);
}

void mostrarIntMap(void *info, size_t tamInfo, size_t nivel, void *param)
{
    printf("%d ", *(int*)info);
}

/// ==================================================================
/// Funciones de tPrueba
/// ==================================================================
int generarLotePrueba(char *nombArch)
{
    tPrueba vecPrueba[] = {
        {10,"pa",123},
        {25,"ab",256},
        {3, "pp",369},
        {46,"nn",254},
        {15,"mm",456},
        {33,"vb",123},
        {88,"vp",125},
        {65,"ov",456},
        {21,"fb",142},
        {58,"xd",321},
        {47,"lo",178},
        {12,"lx",333},
        {95,"db",800},
        {37,"rx",252},
        {45,"rt",655},
        {19,"pt",650},
        {39,"re",280},
    };

    return crearArchBin(nombArch, vecPrueba, sizeof(vecPrueba)/sizeof(*vecPrueba), sizeof(*vecPrueba));
}

void mostrarPruebaCabe()
{
   printf("%5s %10s %5s\n", "CLAVE", "DESC", "CANT");
}
void mostrarPrueba(void *info, void *param)
{
    tPrueba *pru = (tPrueba*)info;
    printf("%5d %10s %5d\n", pru->clave, pru->descrip, pru->cant);
}
void mostrarPruebaClave(void *info, void *param)
{
    tPrueba *pru = (tPrueba*)info;
    printf("%d\n", pru->clave);
}
void mostrarPruebaMap(void *info, size_t tamInfo, size_t nivel, void *param)
{
    tPrueba *pru = (tPrueba*)info;
    printf("%5d %10s %5d\n", pru->clave, pru->descrip, pru->cant);
}
int cmpPrueba(const void* a, const void* b)
{
    tPrueba *p1 = (tPrueba*)a;
    tPrueba *p2 = (tPrueba*)b;

    return p1->clave - p2->clave;
}
int obtenerClavePrueba(void *info)
{
    return ((tPrueba*)info)->clave;
}
int filterMenor(void *info, void *param)
{
    return ((tPrueba*)info)->clave > *(int*)param ? EXITO : 0;
}

/// ==================================================================
/// Funciones de tIndice
/// ==================================================================
void mostrarIndiceCabe()
{
    printf("%5s %5s\n", "CLAVE", "POS");
}
void mostrarIndice(void *info, void *param)
{
    tIndice *ind = (tIndice*)info;
    printf("%5d %5u\n", ind->clave, ind->pos);
}
