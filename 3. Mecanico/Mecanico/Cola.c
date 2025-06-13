
#include <stdlib.h"
#include <string.h>
#include <stdio.h>
#include "Cola.h"


void iniciarCola(Cola* p)
{
    p->pri = NULL;
    p->ult = NULL;
}

void vaciarCola(Cola* p)
{
    while(*p)
    {
        Nodo* aux = *p;
        p->pri = aux;
    }
}
