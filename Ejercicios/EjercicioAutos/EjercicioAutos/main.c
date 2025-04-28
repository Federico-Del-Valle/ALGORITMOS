#include<ColaD.h>



// ==== PRIMITIVAS A IMPLEMENTAR (usar las que hice anteriormente) ====
// ==== esto va en un archivo .h ====

/**
Aqui van sus funciones de contar tiempo y cantidad
funcionQueCuentaLaCantidaddeAutos(...)
funcionQueCuentaEltiempo(...)
 */

// ==== MAIN ====
int main() {
    Cola colaLavadero;
    crearCola(&colaLavadero);
    int opcion;
    Vehiculo v;

    do {
        printf("\n=== Lavadero automatico ===\n");
        printf("1. Llega un auto\n");
        printf("2. Atender proximo auto\n");
        printf("3. Ver cantidad de autos en cola\n");
        printf("4. Ver tiempo de espera \n");
        printf("5. Vaciar cola\n");
        printf("0. Cerrar el negocio\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch(opcion) {
            case 1:
                printf("Patente: ");
                fgets(v.patente, sizeof(v.patente), stdin);
                v.patente[strcspn(v.patente, "\n")] = 0;

                printf("Tipo de vehiculo: ");
                fgets(v.tipo, sizeof(v.tipo), stdin);
                v.tipo[strcspn(v.tipo, "\n")] = 0;

                printf("Tiempo estimado (min): ");
                scanf("%d", &v.tiempo);
                getchar();

                if(ponerEnCola(&colaLavadero, &v, sizeof(Vehiculo)))
                    printf("Vehiculo encolado con exito.\n");
                else
                    printf("Error: no se pudo encolar.\n");
                break;

            case 2:
                if(sacarDeCola(&colaLavadero, &v, sizeof(Vehiculo)))
                    printf("Atendiendo: %s - %s - %d min\n", v.patente, v.tipo, v.tiempo);
                else
                    printf("No hay autos en espera.\n");
                break;

            case 3:
                printf("Autos en cola: %d\n", contarCola(&colaLavadero));
                break;

            case 4:
                printf("El tiempo de espera aproximado es: ...\n");
                break;

            case 5:
                vaciarCola(&colaLavadero);
                printf("Cola vaciada.\n");
                break;

            case 0:
                printf("Cerrando el lavadero...\n");
                vaciarCola(&colaLavadero);
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while(opcion != 5);

    return 0;
}
