#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre[30];
    int edad;
}Persona;

typedef struct NodoArbol
{
    void* info;
    unsigned tamInfo;
    struct NodoArbol* izq;
    struct NodoArbol* der;
}NodoArbol;

typedef NodoArbol* Arbol;
void recorrerEnOrden(Arbol* p, unsigned n, int(*accion)(const void*,unsigned, const void*));
int mostrarPersona(const void* dato, unsigned tamDato, const void* param);
int main()
{
    Arbol arbolPersonas;
    Persona personas[] = {
        {43200123, "Ana", 25},
        {40100234, "Luis", 32},
        {45111222, "Sofia", 28},
        {42000333, "Diego", 21},
        {40000111, "Maria", 30},
        {40050111, "Fede", 32},
    };
    FILE* arch = fopen("personas.dat","wb");
    if(!arch)
    {
        printf("\nERROR AL ABRIR EL ARCHIVO");
        return 0;
    }
    fwrite(personas,sizeof(Persona), sizeof(personas) / sizeof(Persona), arch);

    fclose(arch);
    crearArbol(&arbolPersonas);


    int dni;
    int op;

    do
    {
        printf("--MENU--");
        printf("\n1-Leer archivo y cargar arbol");
        printf("\n2-Mostrar arbol in-order");
        printf("\n3-Seleccione un DNI que desee eliminar");
        printf("\n4-Seleccione un nivel de nodo que desee eliminar");
        printf("\n5-Salir");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cargarArbol(&arbolPersonas, "personas.dat");
            break;
        case 2:
            recorrerEnOrden(&arbolPersonas,0,mostrarPersona);
            break;
        }
    }while(op != 5);

}



void crearArbol(Arbol* p)
{
    *p = NULL;
}


int mostrarPersona(const void* dato, unsigned tamDato, const void* param)
{
    const Persona* per = (Persona*)dato;
    printf("\nLos datos son: %s %d %d", per->nombre, per->edad, per->dni);
    return 1;
}

void recorrerEnOrden(Arbol* p, unsigned n, int(*accion)(const void*,unsigned, const void*))
{
    if(!*p)
        return;
    recorrerEnOrden(&(*p)->izq,n+1,accion);
    accion((*p)->info,(*p)->tamInfo ,NULL);
    recorrerEnOrden(&(*p)->der, n+1, accion);
}




int compararPorDni(const void* dato1, const void* dato2)
{
    const Persona* persona = (const Persona*)dato1;
    const Persona* persona2 = (const Persona*)dato2;

    return persona->dni - persona2->dni;
}

int ponerEnArbolRec(Arbol* p, void* dato, unsigned tamDato,
                    int(*cmp)(const void*, const void*), int(*acumular)(void*, void*))
{
    int rc;
    NodoArbol* nue;

    if (!*p)
    {
        if ((nue = malloc(sizeof(NodoArbol))) == NULL || (nue->info = malloc(tamDato)) == NULL)
        {
            printf("\nERROR");
            free(nue);
            return 0;
        }
        memcpy(nue->info, dato, tamDato);
        nue->tamInfo = tamDato;
        nue->izq = nue->der = NULL;
        *p = nue;
        return 1;
    }

    if ((rc = cmp(dato, (*p)->info)) < 0)
        return ponerEnArbolRec(&(*p)->izq, dato, tamDato, cmp, acumular);
    else if (rc > 0)
        return ponerEnArbolRec(&(*p)->der, dato, tamDato, cmp, acumular);
    else
    {
        if(acumular)
            return acumular((*p)->info, dato);
        return 2; // clave duplicada
    }
}

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
