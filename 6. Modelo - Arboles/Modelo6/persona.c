#include "arbol.h"
#include "persona.h"


int cargarArbol(Arbol* a, const char nombre[])
{
    Persona persona;
    FILE* arch = fopen(nombre, "rb");
    if(!arch)
    {
        printf("\nError al abrir el archivo");
        return 0;
    }

    while(fread(&persona, sizeof(Persona),1, arch) == 1)
    {
        ponerEnArbolRec(a,&persona, sizeof(Persona), compararPorDni, NULL);
    }
    fclose(arch);
    return 1;
}


int eliminarDni(Arbol* p, int dni)
{
    if(!*p)
        return 0;
    Persona* per = (Persona*)(*p)->info;
    if(per->dni > dni)
        return eliminarDni(&(*p)->izq, dni);
    else if(per->dni < dni)
        return eliminarDni(&(*p)->der, dni);
    else
    {
        NodoArbol* elim = *p;
        if(!elim->izq)
            *p= elim->der;
        else if(!elim->der)
            *p= elim->izq;
        else
        {
            NodoArbol** reem = &elim->der;
            while((*reem)->izq)
                reem = &(*reem)->izq;
            void* nuevoDato = malloc((*reem)->tamInfo);
            memcpy(nuevoDato, (*reem)->info,(*reem)->tamInfo);
            free(elim->info);
            return eliminarDni(reem, ((Persona*)nuevoDato)->dni);
        }
        free(elim->info);
        free(elim);
        return 1;
    }
}

