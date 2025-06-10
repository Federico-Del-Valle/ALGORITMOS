#include <stdio.h>
#include <stdlib.h>
#include "pilaDinamica.h"
#include"palindromo.h"


int main()
{

    printf("---Inicio del programa---\n");

    char texto[100];
    fgets(texto, 100, stdin);
    texto[strcspn(texto, "\n")] = '\0';
    FILE* arch = fopen("textoPal.txt", "w");
    if(!arch)
    {
        printf("\nError al abrir el archivo");
        return 0;
    }
    fputs(texto,arch);
    fclose(arch);

    Pila p;
    crearPila(&p);
    if(leerArchEnPila("textoPal.txt", &p))
    {
        printf("\nSe apilo el archivo correctamente\n");
    }else
    {
        printf("Error al apilar el archivo\n");
    }

    if(esPalindromo("textoPal.txt", &p))
    {
        printf("\nEs palindromo");
    }
    else{
        printf("\nNo es palindromo");
    }

    return 1;
}
