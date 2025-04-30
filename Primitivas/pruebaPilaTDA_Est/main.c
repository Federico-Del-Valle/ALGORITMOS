#include "main.h"

int main()
{
    probarIngresarYMostrarProd();

    probarIngresarYMostrarTexto();

    probarPonerYSacarDePila();

    return 0;
}

void probarPonerYSacarDePila(void)
{
    Producto prod, otro;
    char linea[70];
    Pila pila;
    int cant;

    crearPila(&pila);

    puts("Probando primitivas de pila con productos.\n"
         "======== ========== == ==== === =========\n"
         "Probando pila llena y poner en la pila.");

    mostrarProducto(NULL);
    cant = 0;

    while(!pilaLlena(&pila, sizeof(prod)) && ingresarProducto(&prod))
    {
        if(!ponerEnPila(&pila, &prod, sizeof(prod)))
        {
            fprintf(stderr, "ERROR INESPERADO - Pila llena.\n");
            puts("No se pudo cargar la informacion y"
                 "habria que tomar una decision drastica.");
        }
        mostrarProducto(&prod);
        cant++;
    }

    printf("Se pusieron %d productos en la pila.\n\n", cant);
    puts("Probando ver el tope de la pila.");

    if(verTope(&pila, &otro, sizeof(otro)))
    {
        mostrarProducto(NULL);
        mostrarProducto(&otro);
    }
    else
        puts("La pila estaba vacia.\n");

    puts("");
    cant = -2;

    printf("Probando pila vacia y sacar de pila %d productos (Mostrandolos).\n", cant);

    if(pilaVacia(&pila))
        puts("La pila esta vacia.");
    else
        mostrarProducto(NULL);

    while(cant > 0 && sacarDePila(&pila, &prod, sizeof(Producto)))
    {
        cant--;
        mostrarProducto(&prod);
    }

    puts("");
    puts("Probando ver el tope de la pila");

    if(verTope(&pila, &otro, sizeof(otro)))
    {
        puts("La pila no quedo vacia - en el tope hay...");
        mostrarProducto(NULL);
        mostrarProducto(&otro);
    }
    else
        puts("La pila esta vacia");

    puts("");
    puts("Probando vaciar pila y pila vacia.");

    vaciarPila(&pila);

    if(!pilaVacia(&pila))
        fprintf(stderr, "ERROR - La pila debia estar vacia.\n\n");
    else
        printf("Vaciar pila funciona!\n\n");

    puts("");

    puts("Probando primitivas de pila con lineas de texto.\n"
         "======== ========== == ==== === ====== == =====\n"
         "Probando pila llena y poner en pila");

    cant = 0;

    while(!pilaLlena(&pila, sizeof(prod)) && ingresarTexto(linea, sizeof(linea)))
    {
        if(!ponerEnPila(&pila, linea, strlen(linea) + 1))
        {
            fprintf(stderr, "ERROR INESPERADO - Pila llena.\n");
            puts("No se pudo cargarla informacion y"
                 "habria que tomar alguna decision drastica.");
        }
        printf("\"%s\"\n", linea);
        cant++;
    }

    printf("Se pusieron %d lineas de texto en la pila.\n\n", cant);
    printf("Probando sacar de pila con las lineas de texto.\n");
    cant = 0;

    while(sacarDePila(&pila, linea, sizeof(linea)))
    {
        cant++;
        printf("\"%s\"\n", linea);
    }

    printf("Se sacaron y mostraron %d lineas de texto\n\n", cant);
}

void probarIngresarYMostrarProd(void)
{
    Producto prod;
    int cant = 0;

    puts("Probando ingresar productos y mostrar productos.\n"
         "======== ======== ========= = ======= ========= ");

    if(ingresarProducto(&prod))
        mostrarProducto(NULL);

    do
    {
        mostrarProducto(&prod);
        cant++;
    } while(ingresarProducto(&prod));
    fprintf(stdout, "Se mostraron %d productos.\n\n", cant);
}

void probarIngresarYMostrarTexto(void)
{
    char linea[90];
    int cant = 0;

    puts("Probando ingresar lineas de texto mostrandolas.\n"
         "======== ======== ====== == ===== ============ ");

    while(ingresarTexto(linea, sizeof(linea)))
    {
        cant++;
        printf("\"%s\"\n", linea);
    }
    fprintf(stdout, "Se mostraron %d lineas de texto.\n\n", cant);
}
