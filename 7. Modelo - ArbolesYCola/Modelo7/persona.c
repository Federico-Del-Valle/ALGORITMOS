#include "persona.h"


int cargarArbol(Arbol* p, const char nombre[])
{
    Persona persona;
    FILE* arch = fopen(nombre, "rb");
    if(!arch)
    {
        printf("\nError al abrir %s", nombre);
        return 0;
    }
    while(fread(&persona,sizeof(Persona),1,arch) == 1)
    {
        ponerEnArbol(p,&persona, sizeof(Persona),compararPorDni,NULL);
    }
    fclose(arch);
    return 1;
}

int generarArchivo(Cola* p, const char nombre[])
{
    FILE* arch = fopen(nombre, "w");
    if(!arch)
        return 0;
    Persona per;
    while(sacarDeCola(p,&per,sizeof(Persona)) == 1)
    {
        fprintf(arch," %s|%s|%d|%d\n", per.nombre, per.apellido,per.dni, per.edad);
    }
    fclose(arch);
    return 1;
}


int procesarEliminados(Arbol* p, const char nombre[], Cola* c)
{
    FILE* arch = fopen(nombre,"rb");
    if(!arch)
    {
        printf("Error");
        return 0;
    }
    int dni;
    while(fread(&dni, sizeof(int),1,arch) == 1)
    {
        Persona eliminada;
        eliminarPorDni(p,dni,&eliminada, sizeof(Persona));
        ponerEnCola(c,&eliminada,sizeof(Persona));
    }
    fclose(arch);
    return 1;
}
