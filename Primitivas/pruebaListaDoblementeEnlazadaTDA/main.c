#include "main.h"

//TDA LISTA

#define CON_MSJ 1

int compararProductos(const void* a, const void* b) {
    return strcmp(((Producto*)a)->codProd, ((Producto*)b)->codProd);
}

int main()
{
    probarIngresarYMostrarProd();

    //probarIngresarYMostrarTexto();

    probarPonerYSacarDeLista();

    return 0;
}

void probarPonerYSacarDeLista(void)
{
    Lista listaProductos;
    Producto producto;
    crearLista(&listaProductos);

    // Insertar productos al comienzo
    while (ingresarProducto(&producto)) {
        ponerAlComienzo(&listaProductos, &producto, sizeof(Producto));
    }

    // Mostrar la lista de izquierda a derecha
    printf("Lista de productos de izquierda a derecha:\n");
    mostrarDeIzqADer(&listaProductos, (void (*)(const void*))mostrarProducto);

    // Vaciar la lista
    int cantidadEliminada = vaciarLista(&listaProductos);
    printf("\nSe vaciaron %d productos de la lista.\n", cantidadEliminada);

    // Insertar productos al final
    while (ingresarProducto(&producto)) {
        ponerAlFinal(&listaProductos, &producto, sizeof(Producto));
    }

    // Mostrar la lista de derecha a izquierda
    printf("Lista de productos de derecha a izquierda:\n");
    mostrarDeDerAIzq(&listaProductos, (void (*)(const void*))mostrarProducto);

    // Ordenar la lista
    printf("\nOrdenando la lista de productos...\n");
    ordenarLista(&listaProductos, compararProductos);

    // Mostrar la lista ordenada
    printf("Lista de productos ordenada:\n");
    mostrarDeIzqADer(&listaProductos, (void (*)(const void*))mostrarProducto);

    // Eliminar un producto específico
    Producto productoAEliminar = {"martillo3K", ""};
    if (eliminarPorClave(&listaProductos, &productoAEliminar, sizeof(Producto), compararProductos)) {
        printf("\nProducto eliminado: %s\n", productoAEliminar.codProd);
    } else {
        printf("\nProducto no encontrado.\n");
    }

    // Mostrar la lista después de la eliminación
    printf("Lista de productos después de la eliminación:\n");
    mostrarDeIzqADer(&listaProductos, (void (*)(const void*))mostrarProducto);

    // Vaciar la lista nuevamente
    cantidadEliminada = vaciarLista(&listaProductos);
    printf("\nSe vaciaron %d productos de la lista.\n", cantidadEliminada);

    return;
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
