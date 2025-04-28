#include <stdio.h>
#include <stdlib.h>
#include "Pila.h"
int main() {
    tPila historial;

    crearPila(&historial);

    int opcion;
    Pagina pag;

    do {
        printf("\n=== Navegador Web - Historial ===\n");
        printf("1. Visitar nueva página\n");
        printf("2. Volver (Atrás)\n");
        printf("3. Ver página actual\n");
        printf("4. Vaciar historial\n");
        printf("5. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch(opcion) {
            case 1:
                printf("Ingrese URL: ");
                fgets(pag.url, sizeof(pag.url), stdin);
                pag.url[strcspn(pag.url, "\n")] = 0;

                if (apilar(&historial, &pag, sizeof(Pagina)))
                    printf("Página '%s' agregada al historial.\n", pag.url);
                else
                    printf("Error: no se pudo agregar la página.\n");
                break;

            case 2:
                if (desapilar(&historial, &pag, sizeof(Pagina)))
                {
                    verTope(&historial,&pag,sizeof(Pagina));
                    printf("Volviendo a: %s\n", pag.url);
                }

                else
                    printf("No hay más páginas en el historial.\n");
                break;

            case 3:
                if (verTope(&historial, &pag, sizeof(Pagina)))
                    printf("Página actual: %s\n", pag.url);
                else
                    printf("Historial vacío.\n");
                break;

            case 4:
                vaciarPila(&historial);
                printf("Historial vaciado.\n");
                break;

            case 5:
                vaciarPila(&historial);
                printf("Saliendo del navegador...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while(opcion != 5);

    return 0;
}
