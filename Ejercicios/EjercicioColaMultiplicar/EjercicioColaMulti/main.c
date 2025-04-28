#include "Cola.h"

/*Crear una cola de enteros.

Encolar los siguientes valores: 5, 8, 2, 7

Desencolar cada elemento uno por uno.

Por cada valor desencolado, encolarlo nuevamente y luego encolar el doble de ese valor.

Mostrar todos los elementos de la cola final.*/

int main()
{
    int a=5, b=8, d=2, e=7;
    int i = 0;
    Cola c;
    crearCola(&c);
    ponerEnCola(&c,&a,sizeof(a));
    ponerEnCola(&c,&b,sizeof(b));
    ponerEnCola(&c,&d,sizeof(d));
    ponerEnCola(&c,&e,sizeof(e));

    int original;

    while(i < 4)
    {
        sacarCola(&c, &original, sizeof(original));
        int doble = original * 2;
        ponerEnCola(&c, &original, sizeof(original));
        ponerEnCola(&c, &doble, sizeof(doble));
        i++;
    }
    printf("---------------------------------------\n");
    printf("El contenido final de la cola: \n");
    i = 0;
    int aux;
    while(!colaVacia(&c))
    {
        i++;
        sacarCola(&c, &aux, sizeof(aux));
        printf("Elemento %d: %d\n", i, aux);

    }
    return 0;
}
