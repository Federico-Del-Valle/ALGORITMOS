#include "arbol.h"
#include "Pila.h"
#include "cliente.h"
int procesarArch(const char nombre[], Arbol* arbol)
{
    FILE* arch = fopen(nombre, "rb");
    Reclamo reclamo;
    if(!arch)
    {
        printf("\nError al abrir %s", nombre);
        return 0;
    }

    while(fread(&reclamo, sizeof(Reclamo),1, arch) == 1)
    {
        Cliente cliente;
        cliente.idCliente = reclamo.idCliente;
        crearPila(&cliente.reclamos);
        ponerEnPila(&cliente.reclamos, &reclamo, sizeof(Reclamo));
        insertarArbol(arbol, &cliente, sizeof(Cliente), compararPorId, acumular);

    }

    fclose(arch);
    return 1;
}

void procesarArchTexto(void* info, unsigned tamInfo, unsigned nivel, void* params)
{


    Cliente* cliente = (Cliente*)info;
    printf("Procesando cliente %d\n", cliente->idCliente);
    char nombreArchivo[50];
    sprintf(nombreArchivo, "cliente_%d.txt", cliente->idCliente);

    FILE* arch = fopen(nombreArchivo, "w");
    if (!arch) {
        printf("No se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }

    int contador = 0;
    while (cliente->reclamos) {
        Reclamo r;
        memcpy(&r, cliente->reclamos->info, sizeof(Reclamo));

        fprintf(arch, "Reclamo #%d: %s\n", r.idReclamo, r.descripcion);

        Nodo* aux = cliente->reclamos;
        cliente->reclamos = cliente->reclamos->sig;
        free(aux);
        contador++;
    }

    fclose(arch);

    if (contador > 3) {
        printf("Cliente con mas de 3 reclamos (nivel %u): %d\n", nivel, cliente->idCliente);
    }
}

int compararPorId(const void* dato1, const void* dato2)
{
    const Cliente* cliente1 = (const Cliente*)dato1;
    const Cliente* cliente2 = (const Cliente*)dato2;
    return cliente1->idCliente - cliente2->idCliente;
}

int acumular(void* datoExistente, const void* nuevoDato)
{
    Cliente* cliente = (Cliente*)datoExistente;
    const Cliente* clienteNuevo = (const Cliente*)nuevoDato;

    // Este clienteNuevo debería tener al menos un reclamo en su pila
    if (clienteNuevo->reclamos == NULL)
        return 0; // nada que acumular

    Reclamo r;
    memcpy(&r, clienteNuevo->reclamos->info, sizeof(Reclamo));
    return ponerEnPila(&cliente->reclamos, &r, sizeof(Reclamo));
}

