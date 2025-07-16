#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datos.h"
#include "auxiliar.h"
#include "IndiceABB.h"



/** === Función principal === **/

int main()
{
    // Descomente el archivo que quiera leer y probar
    // FILE *f = crearArchivoPrueba();
    // FILE *f = fopen("datos.dat", "rb+");
    // Construir el índice (ABB)
    tArbolBinBusq indice = NULL;
    Registro reg;
    long offset;

     //  FILE *idx = fopen("indice.idx", "rb+");
    // cargarIndiceDesdeArchivo(f, indice, cmpIndice)
    while ((offset = ftell(f)), fread(&reg, sizeof(Registro), 1, f) == 1)
    {
        tIndice ind = { .clave = reg.clave, .offset = offset };
        insertarABB(&indice, &ind, sizeof(tIndice), cmpIndice);
    }

    // Buscar un registro por clave usando el índice
    // Pedir clave al usuario
    int claveBuscada;
    printf("\nIngrese la clave del registro a buscar: ");
    scanf("%d", &claveBuscada);

    tIndice buscado;
    buscado.clave = claveBuscada;
    tIndice *encontrado = NULL;

    if (buscarABB(&indice, &buscado, (void **)&encontrado, cmpIndice))
    {
        fseek(f, encontrado->offset, SEEK_SET); //El 10 es el tercero, desde el inicio me muevo 2 para estar al inicio del registro 3
        fread(&reg, sizeof(Registro), 1, f);
        //Aca modifico el tercer registro

        //lo tengo que guardar
        fseek(f, -1*sizeof(Registro), SEEK_CUR); //El 10 es el tercero, desde el inicio me muevo 2 para estar al inicio del registro 3
        fseek(f, 0, SEEK_CUR); //e
        printf("Registro encontrado: Clave=%d, Nombre=%s\n", reg.clave, reg.nombre);
    }
    else
    {
        printf("Registro con clave %d no encontrado.\n", claveBuscada);
    }

    FILE *idx = fopen("indice.idx", "wb");
    guardarIndiceEnArchivo(idx, indice);
    // Limpieza
    destruirABB(&indice);
    fclose(f);
    return 0;
}
