#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

void* map(void* vec, unsigned ce, unsigned tam, int accion(void*));
void* filter(void* vec, unsigned* ce, unsigned tam, int ffiltro(const void*));
void* reduce(void* vec, unsigned ce, unsigned tam, void* (*reductor)(void*, const void*), void* acum);

//////////////////////////////////////////////////////////

//MAP (OPERAR SOBRE TODOS)
int raizCuadrada(void* info)
{
    float* puntinfo =  (float*) info;
    *puntinfo = sqrt(*puntinfo);

    return 1;
}

int mostrarFloat(void* info)
{
    return printf("%5.2f", *(float*)info);
}

int mostrarEntero(void* info)
{
    return printf("%5d", *(int*)info);
}


//FILTER (FILTRAR LOS QUE NO CUMPLEN X CONDICION)
int distDeTres(const void* x)
{
    return(*(int*)x) != 3;
}


//REDUCE (COMBINAR TODOS EN UNO)
void* sumarEnteros(void* acum, const void* actual)
{
    *(int*)acum += *(int*)actual;
    return acum;
}

void* multiplicarEnteros(void* acum, const void* actual)
{
    *(int*)acum *= *(int*)actual;
    return acum;
}

//////////////////////////////////////////////////////////

int main()
{
    /*float vec[] = {16.0, 4.0, 9.0, 25.0, 81.0};
    unsigned ce = 5;

    map(vec, ce, sizeof(float), raizCuadrada);
    map(vec, ce, sizeof(float), mostrarFloat);*/

    /*int vec[] = {6, 3, 7, 3, 3, 9, 18, 3};
    unsigned ce = sizeof(vec)/sizeof(vec[0]);
    int tam = sizeof(*vec);

    filter(vec, &ce, tam, distDeTres);

    map(vec, ce, tam, mostrarEntero);*/

    int vec[] = {1, 2, 3, 4, 5};
    unsigned ce = sizeof(vec)/sizeof(vec[0]);
    int resultadoSuma = 0;
    int resultadoProducto = 1;

    reduce(vec, ce, sizeof(int), sumarEnteros, &resultadoSuma);
    printf("Suma total: %d\n", resultadoSuma);

    reduce(vec, ce, sizeof(int), multiplicarEnteros, &resultadoProducto);
    printf("Producto total: %d\n", resultadoProducto);

    return 0;
}

void* map(void* vec, unsigned ce, unsigned tam, int accion(void*))
{
    int i;
    void* ini = vec;

    for(i = 0; i < ce; i++)
    {
        accion(vec);
        vec += tam;
    }
    return ini;
}

void* filter(void* vec, unsigned* ce, unsigned tam, int ffiltro(const void*))
{
    void* pl = vec; //Puntero de lectura
    void* pe = vec; //Puntero de escritura
    int i;
    unsigned ceInterna = *ce;

    for(i = 0; i < *ce; i++)
    {
        if(ffiltro(pl))
        {
            if(pe != pl)
                memcpy(pe, pl, tam);
            pe += tam;
        }
        else
            ceInterna--;

        pl += tam;
    }

    *ce = ceInterna;

    return vec;
}

void* reduce(void* vec, unsigned ce, unsigned tam, void* (*reductor)(void*, const void*), void* acum)
{
    int i;
    for(i = 0; i < ce; i++)
    {
        reductor(acum, vec);
        vec += tam;
    }
    return acum;
}
