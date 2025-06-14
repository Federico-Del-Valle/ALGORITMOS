#include <stdio.h>
#include <stdlib.h>

int main()
{

    int op = 0;
    while(op!= 6)
    {
        printf("--MENU--\n");
        printf("\n1- Agregar cliente junto a sus reclamos");
        printf("\n2- Atender cliente");
        printf("\n3- Vaciar sistema");
        printf("\n6- Salir del programa");
        scanf("\n%d", &op);
    }

}
