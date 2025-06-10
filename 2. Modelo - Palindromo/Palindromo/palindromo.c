#include <stdio.h>
#include "pilaDinamica.h"
#include "palindromo.h"


/*
@param recibe un archivo y una pila
@return retorna 1 si salio bien
*/

int leerArchEnPila(const char arch[], Pila* p)
{

    char linea[100];

    FILE* archivo = fopen(arch, "r");
    if(!archivo)
    {
        printf("Error al abrir el archivo");
        return 0;
    }
    while(fgets(linea, 100, archivo))
    {
        int i = 0;
        while(linea[i] != '\0')
        {
            if(linea[i]!= ' ' && linea[i] != '\n')
            {
                ponerEnPila(p, &linea[i], sizeof(char));
            }
            i++;
        }
    }
    fclose(archivo);

    return 1;
}

int esPalindromo(const char nombre[], Pila* p)
{
    FILE* archivo = fopen(nombre, "r");
    if(!archivo)
    {
        printf("\nError al abrir el archivo");
        return 0;
    }
    char c;
    char tope;

    while( (c =fgetc(archivo)) != EOF)
    {
        if(c != ' ')
        {
            verTope(p, &tope, sizeof(char));
            if(tolower(c) == tolower(tope))
            {
                sacarDePila(p, &c, sizeof(char));
            }
            else
            {
                fclose(archivo);
                return 0;
            }
        }


    }
    fclose(archivo);
    return 1;
}
