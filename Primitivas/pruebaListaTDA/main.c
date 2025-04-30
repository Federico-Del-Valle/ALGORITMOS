#include "main.h"

//TDA LISTA

#define CON_MSJ 1

int _abrirArchivo(FILE** fp, const char* nomArch, const char* modo, int conSinMsj)
{
    *fp = fopen(nomArch, modo);

    if(*fp == NULL)
    {
        if(conSinMsj == CON_MSJ)
            fprintf(stderr,
                    "ERROR - Abriendo archivo \"%s\" en modo \"%s\".\n",
                    nomArch, modo ? modo : "NULL");
        return 0;
    }

    return 1;
}

void _verYCerrarArchivo(FILE* fp, const char* nomArch)
{
    char comando[50];

    if(fp == stdout || fp == stderr)
        return;
    fflush(fp);
    fclose(fp);

    sprintf(comando, "start /low notepad.exe %s", nomArch);
    system(comando);
}

int _probarPonerAlComienzo(Lista* lista, FILE* fp)
{
    Producto prod;
    int cant = 0;

    fprintf(fp, "- Probando poner al comienzo.\n");
    if(ingresarProducto(&prod))
        mostrarProductoTxt(NULL, fp);

    do
    {
        if(!ponerAlComienzo(lista, &prod, sizeof(prod)))
        {
            fprintf(stderr, "ERROR INESPERADO - Lista llena.\n"
                    "Producto no cargado: \n");
            mostrarProductoTxt(&prod, stderr);
        }
        else
        {
            cant++;
            mostrarProductoTxt(&prod, fp);
        }
    }while(ingresarProducto(&prod));

    fprintf(fp, "Se pusieron al comienzo de la lista %d productos.\n", cant);
    return cant;
}

int _probarPonerAlFinal(Lista* lista, FILE* fp)
{
    Producto prod;
    int cant = 0;

    fprintf(fp, "- Probando poner al final.\n");
    if(ingresarProducto(&prod))
        mostrarProductoTxt(NULL, fp);

    do
    {
        if(!ponerAlFinal(lista, &prod, sizeof(prod)))
        {
            fprintf(stderr, "ERROR INESPERADO - Lista llena.\n"
                    "Producto no cargado: \n");
            mostrarProductoTxt(&prod, stderr);
        }
        else
        {
            cant++;
            mostrarProductoTxt(&prod, fp);
        }
    }while(ingresarProducto(&prod));

    fprintf(fp, "Se pusieron al final de la lista %d productos.\n", cant);
    return cant;
}

int _probarSacarNCom(Lista* lista, FILE* fp, int n)
{
    Producto prod;
    int cant = 0;

    fprintf(fp, "- Probando sacar del comienzo de la lista %d productos.\n", n);
    if(sacarPrimeroLista(lista, &prod, sizeof(prod)))
        mostrarProductoTxt(NULL, fp);

    do
    {
        mostrarProductoTxt(&prod, fp);
        cant++;
    }while(--n && sacarPrimeroLista(lista, &prod, sizeof(prod)));

    /* ACLARACION
    n = 5;
    x = --n;   n se convierte en 4 y x toma el valor 4

    n = 5;
    x = n--;   x toma el valor 5 y n se convierte en 4

    n-- != --n
    */

    if(cant)
        fprintf(fp, "Se sacaron del comienzo de la lista %d productos.\n", cant);
    else
        fprintf(fp, "La listaba estaba vacia - No se pudo sacar del comienzo.\n");

    fprintf(fp, "La lista %squedo vacia.\n", listaVacia(lista) ? "" : "no "); //Muy bueno

    return cant;
}

int _probarSacarNFin(Lista* lista, FILE* fp, int n)
{
    Producto prod;
    int cant = 0;

    fprintf(fp, "- Probando sacar del final de la lista %d productos.\n", n);
    if(sacarUltimoLista(lista, &prod, sizeof(prod)))
        mostrarProductoTxt(NULL, fp);

    do
    {
        mostrarProductoTxt(&prod, fp);
        cant++;
    }while(--n && sacarUltimoLista(lista, &prod, sizeof(prod)));

    if(cant)
        fprintf(fp, "Se sacaron del final de la lista %d productos.\n", cant);
    else
        fprintf(fp, "La listaba estaba vacia - No se pudo sacar del final.\n");

    fprintf(fp, "La lista %squedo vacia.\n", listaVacia(lista) ? "" : "no "); //Muy bueno

    return cant;
}

int _probarVaciarLista(Lista* lista, FILE* fp)
{
    int cant = 0;

    fprintf(fp, "- Probando vaciar y mostrar lista.\n");
    if(!listaVacia(lista))
        mostrarProductoTxt(NULL, fp);
    cant = vaciarListaYMostrar(lista, mostrarProductoTxtTDA, fp);
    fprintf(fp, "Se eliminaron y mostraron %d elementos de la lista.\n", cant);
    return cant;
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
    Lista lista;
    int veces;
    FILE* fp;
    char nomArch[] = { "Salida" };

    crearLista(&lista);

    veces = 2;
    fp = stdout;

    while(veces--)
    {
        int cantCom, cantFin, cantElimCom, cantElimFin, cantElimTot;

        cantCom = _probarPonerAlComienzo(&lista, fp);
        printf("***Se pusieron %d elementos al comienzo***\n\n", cantCom);
        cantFin = _probarPonerAlFinal(&lista, fp);
        printf("***Se pusieron %d elementos al final***\n\n", cantFin);
        cantElimCom = _probarSacarNCom(&lista, fp, 3);
        printf("***Se sacaron %d elementos del comienzo***\n\n", cantElimCom);
        cantElimFin = _probarSacarNFin(&lista, fp, 2);
        printf("***Se sacaron %d elementos del final***\n\n", cantElimFin);
        cantElimTot = _probarVaciarLista(&lista, fp);
        printf("***Se eliminaron %d elementos al vaciar la lista***\n\n", cantElimTot);

        if(!_abrirArchivo(&fp, nomArch, "wt", CON_MSJ))
            fp = stderr;
    }

    _verYCerrarArchivo(fp, nomArch);
    if(!listaVacia(&lista))
    {
        printf("***ERROR - La lista deberia estar vacia.***\n"
               "Se procede a vaciarla.\n");
        vaciarLista(&lista);
    }
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
