#include "ColaD.h"

int main()
{
    Cola c;
    crearCola(&c);
    int a = 10, b= 20, ci = 30;
    ponerEnCola(&c,&a, sizeof(a));
    ponerEnCola(&c,&b,sizeof(b));
    ponerEnCola(&c,&ci,sizeof(ci));
    int primero, x, i =1;
    if(verPrimeroCola(&c,&primero,sizeof(primero)))
       {
           printf("\nPrimero de la cola: %d\n", primero);
       }
    while(!colaVacia(&c))
        {
            sacarCola(&c,&x,sizeof(x));
            printf("El elemento %d es: %d\n", i,x);
            i++;
        }

    return 0;
}
