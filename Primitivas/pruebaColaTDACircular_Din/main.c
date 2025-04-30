#include "main.h"

//COLA DINAMICA

int main()
{
    //probarIngresarYMostrarProd();

    //probarIngresarYMostrarTexto();

    probarPonerYSacarDeCola();

    return 0;
}

int _probarLlenaYEncolar(Cola* cola)
{
    Producto prod;
    int cant = 0;

    puts("Probando cola llena y poner en cola.");
    mostrarProducto(NULL);
    while(!colaLlena(cola, sizeof(prod)) && ingresarProducto(&prod))
    {
        if(!ponerEnCola(cola, &prod, sizeof(prod)))
        {
            fprintf(stderr, "ERROR INESPERADO - Cola llena.\n");
            puts("No se pudo cargar la informacion y"
                 "habria que tomar alguna decision drastica.");
        }
        mostrarProducto(&prod);
        cant++;
    }
    return cant;
}

void _probarVerTope(Cola* cola)
{
    Producto prod;

    puts("Probando ver el primero de la cola.\n");
    if(verPrimeroCola(cola, &prod, sizeof(prod)))
    {
        mostrarProducto(NULL);
        mostrarProducto(&prod);
    }
    else
        puts("La cola estaba vacia.\n");
}

void _probarVaciaYDesacolarN(Cola* cola, int cantidad)
{
    Producto prod;

    printf("Probando cola vacia y sacar de cola %d productos (Mostrandolos)\n", cantidad);

    if(colaVacia(cola))
        puts("La cola esta vacia");
    else
        mostrarProducto(NULL);

    while(cantidad > 0 && sacarDeCola(cola, &prod, sizeof(prod)))
    {
        cantidad--;
        mostrarProducto(&prod);
    }
    puts("");
}

int _probarVaciarColaYColaVacia(Cola* cola)
{
    puts("Probando vaciar cola y cola vacia.");
    vaciarCola(cola);
    if(!colaVacia(cola))
    {
        fprintf(stderr, "ERROR - La cola debia estar vacia.\n\n");
        return 0;
    }
    printf("Vaciar la cola funciona!\n\n");
    puts("");

    return 1;
}

void _probarLlenaYEncolarTexto(Cola* cola)
{
    char linea[70];
    int cant = 0;

    puts("Probando cola llena y poner texto en cola.");
    while(!colaLlena(cola, sizeof(linea)) && ingresarTexto(linea, sizeof(linea)))
    {
        if(!ponerEnCola(cola, linea, strlen(linea) + 1))
        {
            fprintf(stderr, "ERROR INESPERADO - Cola llena.\n");
            puts("No se pudo cargar la informacion y"
                 "habria que tomar una decision drastica.\n");
        }
        printf("\"%s\"\n", linea); // con  \" imprimo comillas
        cant++;
    }

    printf("Se pusieron %d lineas de texto en la cola.\n\n", cant);
}

void _probarSacarDeColaTexto(Cola* cola)
{
    char linea[70];
    int cant = 0;

    while(sacarDeCola(cola, linea, sizeof(linea)))
    {
        cant++;
        printf("\"%s\"\n", linea);
    }
    printf("Se sacaron y mostraron %d lineas de texto\n\n", cant);
}

void probarPonerYSacarDeCola(void)
{
    Cola cola;
    int cant;

    crearCola(&cola);

    puts("Probando primitivas de cola con productos\n"
         "======== ========== == ==== === =========\n");

    cant = _probarLlenaYEncolar(&cola);
    printf("Se pusieron %d productos en la cola.\n\n", cant);

    _probarVerTope(&cola);

    _probarVaciaYDesacolarN(&cola, cant - 2);

    _probarVerTope(&cola);

    if(_probarVaciarColaYColaVacia(&cola) != 1)
        fprintf(stderr, "ERROR INESPERADO - La cola NO quedo vacia.\n\n");

    puts("Probando primitivas de cola con lineas de texto.\n"
         "======== ========== == ==== === ====== == =====\n");

    _probarLlenaYEncolarTexto(&cola);

    _probarSacarDeColaTexto(&cola);
    cant = 0;

    puts("Proceso finalizado con exito...\n");
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
