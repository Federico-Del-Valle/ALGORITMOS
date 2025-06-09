#include <stdio.h>
#include "pilaDinamica.h"
#include "palindromo.h"


/*
@param recibe un archivo y una pila
@return retorna 1 si salio bien
*/

int leerArchEnPila(const char arch[], Pila* p)
{
    int i = 0;
    char linea[100];

    FILE* archivo = fopen(arch, "r");
    if(!archivo)
    {
        printf("Error al abrir el archivo");
        return 0;
    }
    while(fgets(linea, 100, archivo))
    {
        printf("%s", linea);
    }
    while(linea[i] != '\0')
    {
        if(linea[i]!= ' ')
        {
            ponerEnPila(&p, linea[i], sizeof(char));
            i++;
        }
        else
        {
            i++;
        }
    }
    return 1;
}
