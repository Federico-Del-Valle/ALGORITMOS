#include "parcial.h"
#define MIN(a,b) ((a)<(b)?(a):(b))



//FUNCIONES ARBOLES

void crearArbol(Arbol* arbol)
{
    *arbol = NULL;
}

int ponerEnArbol(Arbol* p, void* d, unsigned tamDato, int(*cmp)(const void*, const void*))
{
    NodoArbol* nue;
    int rc;

    while(*p)
    {
        if((rc= cmp(d,(*p)->info)) < 0)
            return ponerEnArbol(&(*p)->izq,d,tamDato,cmp);
        else if(rc > 0)
            return ponerEnArbol(&(*p)->der, d, tamDato, cmp);
        else
            return 2;
    }
    if((nue = malloc(sizeof(NodoArbol))) == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }
    nue->tamInfo = tamDato;
    memcpy(nue->info, d,tamDato);
    nue->izq = NULL;
    nue->der = NULL;
    *p=nue;

    return 1;
}


void vaciarArbol(Arbol* p)
{
    if (!*p)
        return;

    vaciarArbol(&(*p)->izq);
    vaciarArbol(&(*p)->der);

    free((*p)->info);
    free(*p);
    *p = NULL;
}


void grabarArbolEnArchivo(Arbol* arbol, const char* nombreArchivo)
{
    FILE* arch = fopen(nombreArchivo, "wb");
    if (!arch)
    {
        printf("Error al abrir %s para escritura\n", nombreArchivo);
        return;
    }

    recorrerEnOrdenRecArbolBinBusq(arbol, 0, arch, accionGrabarIndice);
    fclose(arch);
    printf("Arbol grabado correctamente en %s\n", nombreArchivo);
}


NodoArbol** buscarNodo(const Arbol* p, const void* d, int(*cmp)(const void*, const void*))
{
    int rc;
    while(*p && (rc = cmp(d, (*p)->info)))
    {
        if(rc < 0)
            p= &(*p)->izq;
        else
        p=&(*p)->der;
    }
    if(!*p)
        return NULL;
    return (NodoArbol**)p;
}

int buscarEnArbol(Arbol* p, void* dato, unsigned tamDato, int(*cmp)(const void*, const void*))
{
    NodoArbol** nodo;
    if(!(nodo=buscarNodo(p,dato,cmp)))
        return 0; //no se encontro
    memcpy(dato, (*nodo)->info, MIN(tamDato, (*nodo)->tamInfo));
    return 1;
}



// Punto 1

int darDeBaja(Arbol* p,int dni, char nombre[])
{
    Indice idxBuscar;
    idxBuscar.dni = dni;

    NodoArbol** nodo = buscarNodo(p, &idxBuscar, cmpDni);

    if (!nodo) {
        printf("\nDNI no encontrado\n");
        return 0;
    }

    FILE* arch = fopen(nombre, "rb+");
    if (!arch) {
        printf("\nError al abrir el archivo %s\n", nombre);
        return 0;
    }

    Indice* idx = (Indice*)(*nodo)->info;
    Alumno alu;
    fseek(arch, idx->indice * sizeof(Alumno), SEEK_SET);
    fread(&alu, sizeof(Alumno), 1, arch);

    if (alu.estado == 'B') {
        printf("El alumno ya estaba dado de baja.\n");
        fclose(arch);
        return 0;
    }

    alu.estado = 'B';
    fseek(arch, -sizeof(Alumno), SEEK_CUR);
    fwrite(&alu, sizeof(Alumno), 1, arch);
    fclose(arch);
    printf("Alumno dado de baja correctamente.\n");
    return 1;
}


void accionMostrarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params)
{
    const Indice* ind = (const Indice*)info;
    printf("DNI: %d, Registro: %d\n", ind->dni, ind->indice);
}


void accionGrabarIndice(void* info, unsigned tamInfo, unsigned nivel, void* params)
{
    FILE* f = (FILE*)params;
    fwrite(info, tamInfo, 1, f);
}


void cargarArbolDesordenado(Arbol* arbolIndice, char nombre[])
{
    printf("\nIniciando carga del arbol desde archivo alumnos.dat\n");

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
        ind.indice = nroReg++;
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
    printf("Indice grabado correctamente en alumnos.idx\n");
}


int cmpDni(const void* dato1, const void* dato2)
{
    const Indice* d1 = (const Indice*)dato1;
    const Indice* d2 = (const Indice*)dato2;
    return d1->dni-d2->dni;
}



void recorrerEnOrdenRecArbolBinBusq(const Arbol * p, unsigned n, void * params,
                                    void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenRecArbolBinBusq(&(*p)->der, n+1, params, accion);
}
