#include <stdio.h>
#include <stdlib.h>

int main()
{
    char cadena[100] = [];

    FILE* archivo = fopen("texto.txt", "r");

    if(!archivo)
    {
        printf("No se pudo abrir el archivo");
        return 0;
    }

    fgets(cadena,100,archivo);

    for(int i = 0; cadena[i] != '\0'; i++)
    {

    }


}
