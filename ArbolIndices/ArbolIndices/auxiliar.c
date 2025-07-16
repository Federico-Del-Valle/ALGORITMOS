#include "datos.h"

/** === Función de comparación para índice === **/

int cmpIndice(const void *a, const void *b) {
    return ((tIndice *)a)->clave - ((tIndice *)b)->clave;
}


FILE* crearArchivoPrueba(){

FILE *f = fopen("datos.dat", "wb+");
    if (!f) {
        perror("Error al abrir datos.dat");
        return NULL;
    }

    // Crear registros de ejemplo desordenados
    Registro registros[] = {
        {23, "Juan"},
        {5, "Ana"},
        {15, "Luis"},
        {42, "Marta"},
        {8, "Carlos"}
    };

    printf("=== Registros insertados ===\n");
    for (int i = 0; i < 5; i++) {
        fwrite(&registros[i], sizeof(Registro), 1, f);
        printf("Clave=%d, Nombre=%s\n", registros[i].clave, registros[i].nombre);
    }

    rewind(f);
    return f;
}
