#include "parcial.h"


//FUNCIONES ARBOLES

void crearArbol(Arbol* arbol)
{
    *arbol = NULL;
}


void accionGrabarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params)
{
    FILE* f = (FILE*)params;
    fwrite(info, tamInfo, 1, f);
}

int cmpDni(const void* dato1, const void* dato2)
{
    const Indice* d1 = (const Indice*)dato1;
    const Indice* d2 = (const Indice*)dato2;
    return d1->dni - d2->dni;
}

void cargarArbolDesordenado(Arbol* arbolIndice, char nombre[])
{
    printf("\nIniciando carga del árbol desde archivo alumnos.dat\n");

    Alumno alum;
    Indice ind;
    int nroReg = 0;

    FILE* arch = fopen(nombre, "rb");
    if (!arch)
    {
        printf("Error al abrir %s\n", nombre);
        return;
    }

    while (fread(&alum, sizeof(Alumno), 1, arch) == 1)
    {
        ind.dni = alum.dni;
        ind.nroRegistro = nroReg++;
        ponerEnArbol(arbolIndice, &ind, sizeof(Indice), cmpDni);
    }
    fclose(arch);

    // Ahora grabamos el árbol en orden en alumnos.idx
    FILE* archIdx = fopen("alumnos.idx", "wb");
    if (!archIdx)
    {
        printf("Error al crear alumnos.idx\n");
        return;
    }

    recorrerEnOrdenRecArbolBinBusq(arbolIndice, 0, archIdx, accionGrabarIndice);
    fclose(archIdx);
    printf("Índice grabado correctamente en alumnos.idx\n");
}


int cmpDni(const void* dato1, const void* dato2)
{
    const Indice d1 = (const Indice*)dato1;
    const Indice d2 = (const Indice*)dato2;
    return d1->dni-d2->dni;
}

void grabarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params)
{
    FILE* f = (FILE*)params;
    fwrite(info, tamInfo,1,f);
}


void recorrerEnOrdenRecArbolBinBusq(const ArbolBinBusq * p, unsigned n, void * params,
                                    void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenRecArbolBinBusq(&(*p)->der, n+1, params, accion);
}
