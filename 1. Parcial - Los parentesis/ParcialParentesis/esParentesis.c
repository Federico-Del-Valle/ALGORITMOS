#include"esParentesis.h"
#include "pilaDinamica.h"





int chequearSiEsParentizado(char nombre[], Pila* p)
{
    char texto[100];
    int i = 0;
    FILE* archivo = fopen(nombre,"r");
    if(!archivo)
    {
        printf("Error al abrir el archivo de texto");
        return 0;
    }

    fgets(texto, 100,archivo);

    while(texto[i] != '\0' )
    {
        char actual = texto[i];

        if(actual == '{' || actual == '(' || actual == '[')
            {
                ponerEnpila(p,&actual, sizeof(char));
            }
            else
                {
                    char tope;
                    if(!verTope(p,&tope, sizeof(char)))
                    {
                        return 0;
                    }
                    else
                    {
                        int esPar= 0;
                        if(actual == ')' && tope == '(')
                            esPar= 1;
                        if(actual ==']' && tope == '[')
                            esPar =1;
                        if(actual == '}' && tope == '{')
                            esPar = 1;
                        if(!esPar)
                            return 0;
                        sacarDePila(p, &tope,sizeof(char));
                    }
                }
                i++;
    }
    return pilaVacia(p);
}
