#include <stdio.h>
#include <stdlib.h>

int main()
{
    int op;

    printf("\nMENU");
    do
    {
        printf("\nSeleccione una opcion:");
        printf("\n1- Cargar arbol");
        printf("\n2- Dar baja producto");
        printf("\n3- Ver si es completo");
        printf("\n4- Ver si es AVL");
        printf("\n5- Mostrar arbol");
        printf("\n6- Salir");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cargarArbol(&arbolIdx, "Productos.dat");
            break;

        case 2:
            break;

        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;

        }
    }while(op != 6);




    return 0;
}
