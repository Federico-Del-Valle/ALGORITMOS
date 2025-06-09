#include <stdio.h>
#include <stdlib.h>
#include "pilaDinamica.h"
#include"palindromo.h"


int main()
{
    Pila p;
    crearPila(&p);
    if(leerArchEnPila("textoPal.txt", &p))
    {
        printf("\nSe apilo el archivo correctamente\n");
    }else
    {
        printf("Error al apilas el archivo\n");
    }


}
