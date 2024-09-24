#include "main.h"

int main()
{
    probarIngresarYMostrarProd();
    probarIngresarYMostrarTexto();
    return 0;
}


void probarIngresarYMostrarProd(void)
{
    tprod prod;
    int cant = 0;

    puts("Probando ingresar productos y msotrar productos. \n");
    printf("%-20s %-30s\n", "Producto", "Descripcion");

    if(ingresarProd(&prod))
        mostrarProd(NULL);
    do
    {
        mostrarProd(&prod);
        cant++;
    }while(ingresarProd(&prod));

    fprintf(stdout,"\nSe mostraron %d productos. \n\n", cant);
}

void probarIngresarYMostrarTexto(void)
{
    char linea[90];
    int cant = 0;
    puts("Probando ingresar lineas de texto mostrandolas. \n"
         "======= ====== ==== ====== ===========");
         while(ingresarTexto(linea, sizeof(linea)))
         {
             cant++;
             printf("\"%s""\n", linea);
         }
    fprintf(stdout, "Se mostraron %d lineas de texto.\n\n", cant);
}

void probarPonerYSacarDePila(void)
{
    tPila pila;
    crearPila(&pila);

}
