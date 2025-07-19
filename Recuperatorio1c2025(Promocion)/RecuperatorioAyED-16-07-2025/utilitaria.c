#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "arbol_bin_busq.h"
#include "utilitaria.h"
#include <string.h>
#include "cola.h"
#define minimo(x,y) ( (x) < (y) ? (x) : (y))

void mostrarPacienteConRecuadro(const tPaciente* p)
{
    char buffer[128];
    const int ancho = 60;

    printf("|------------------------------------------------------------|\n");
    // Líneas de contenido
    snprintf(buffer, sizeof(buffer), "Paciente #%d", p->numeroPaciente);
    printf("| %-*s |\n", ancho - 2, buffer);

    snprintf(buffer, sizeof(buffer), "DNI: %ld", p->dni);
    printf("| %-*s |\n", ancho - 2, buffer);

    snprintf(buffer, sizeof(buffer), "Nombre y Apellido: %s", p->nombreApellido);
    printf("| %-*s |\n", ancho - 2, buffer);

    snprintf(buffer, sizeof(buffer), "Obra Social: %s", p->obraSocial);
    printf("| %-*s |\n", ancho - 2, buffer);

    snprintf(buffer, sizeof(buffer), "Cantidad de Consultas: %d", p->cantidadConsultas);
    printf("| %-*s |\n", ancho - 2, buffer);

    snprintf(buffer, sizeof(buffer), "Monto Invertido: $%.2f", p->montoInvertido);
    printf("| %-*s |\n", ancho - 2, buffer);
    printf("|------------------------------------------------------------|\n");

}
//Metodo NO ptimo solo con fines pedagogicos
void abrirYMostrarPacientes()
{
    FILE* f = fopen("pacientes.dat", "rb");
    tPaciente p;

    printf("|============================================================|\n");
    printf("|================ Listado completo de Pacientes =============|\n");
    printf("|============================================================|\n");
    while (fread(&p, sizeof(tPaciente), 1, f) == 1)
    {
        mostrarPacienteConRecuadro(&p);
    }
    printf("|============================================================|\n");

    fclose(f);

}

//Metodo NO ptimo solo con fines pedagogicos
void abrirYMostrar10Pacientes()
{
    FILE* f = fopen("pacientes.dat", "rb");
    tPaciente p;
    int i;

    printf("|============================================================|\n");
    printf("|================ Listado 10 Primeros Pacientes =============|\n");
    printf("|============================================================|\n");
    for(i=0; i<10; i++)
    {
        if(fread(&p, sizeof(tPaciente), 1, f) == 1)
        {
            mostrarPacienteConRecuadro(&p);
        }
    }
    printf("|============================================================|\n");

    fclose(f);

}

int cmpInd(const void* d, const void* d2)
{
    const Indice* ind1 = (const Indice*)d;
    const Indice* ind2 = (const Indice*)d2;
    return ind1->nroPaciente - ind2->nroPaciente;
}
//Punto 1

int cargarArbolIdx(tArbolBinBusq* p, char nombre[])
{
    Indice ind;
    tPaciente paciente;
    int nroReg = 0;

    FILE* arch = fopen(nombre, "rb");
    if(!arch)
    {
        printf(("\nError"));
        return 0;
    }

    while(fread(&paciente, sizeof(tPaciente),1,arch) == 1)
    {
        ind.nroReg = nroReg;
        ind.nroPaciente = paciente.numeroPaciente;
        insertarRecArbolBinBusq(p,&ind, sizeof(Indice),cmpInd);
        nroReg++;
    }
    fclose(arch);
    return 1;
}
//DAR DE ALTA PACIENTE
int darAlta(tArbolBinBusq* p, FILE* f)
{
    if(!f)
    {
        printf("\nError");
        return 0;
    }

    tPaciente paciente = {43316258, "Federico Del Valle", "IOMA",3333, 3, 40};
    Indice ind;
    ind.nroPaciente = paciente.numeroPaciente;
    fseek(f,0,SEEK_END);
    fwrite(&paciente,sizeof(tPaciente),1,f);
    insertarArbolBinBusq(p,&ind, sizeof(Indice),cmpInd);
    printf("\nSe dio de alta el paciente nro: %d", ind.nroPaciente);
    return 1;
}

//DAR DE BAJA PACIENTE

int darDeBaja(tArbolBinBusq* p, int nroPaciente, FILE* f)
{
    if(!f)
    {
        printf("\nERROR");
        return 0;
    }
    rewind(f);
    tPaciente paciente;
    Indice ind;
    ind.nroPaciente = nroPaciente;
    if(buscarElem(p,&ind,sizeof(Indice),cmpInd) != 1)
    {
        printf("\nNo existe ese paciente");
        return 0;
    }
    fseek(f,ind.nroReg * sizeof(tPaciente),SEEK_SET);
    fread(&paciente,sizeof(tPaciente),1,f);
    paciente.numeroPaciente = 0;
    fseek(f,ind.nroReg * sizeof(tPaciente),SEEK_SET);
    fwrite(&paciente,sizeof(tPaciente),1, f);

    if(eliminarElem(p,&ind,sizeof(Indice),cmpInd) != 1)
    {
        return 0;
    }

    printf("\nSe elimino el paciente: %d", ind.nroPaciente);
    return 1;
}

int insertarArbol(tArbolBinBusq* p, const void* d, unsigned tam, int(*cmp)(const void*, const void*))
{
    tNodoArbol* nue;
    int rc;
    while(*p)
    {
        if((rc = cmp(d,(*p)->info))< 0)
            return insertarArbol(&(*p)->izq, d, tam,cmp);
        else if(rc > 0)
            return insertarArbol(&(*p)->der,d,tam,cmp);
        else
            return 2; //dato duplicado;
    }
    if((nue = malloc(sizeof(tNodoArbol))) == NULL || (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,tam);
    nue->tamInfo = tam;
    nue->der = NULL;
    nue->izq = NULL;

    return 1;
}

int eliminarRaiz(tArbolBinBusq* p)
{
    tNodoArbol** remp;
    tNodoArbol* elim;
    if(!*p)
        return 0;
    free((*p)->info);
    if(!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return 1;
    }
    remp = alturaArbol(&(*p)->izq) > alturaArbol(&(*p)->der) ? mayorNodo(&(*p)->izq) : menorNodo(&(*p)->der);
    elim = *remp;
    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;
    *remp = elim->izq ? elim->izq : elim->der;
    free(elim);
    return 1;
}

tNodoArbol** mayorNodo(tArbolBinBusq* p)
{
    if(!(*p)->der)
        return (tNodoArbol**)p;
    return mayorNodo(&(*p)->der);
}


tNodoArbol** menorNodo(tArbolBinBusq* p)
{
    if(!(*p)-> izq)
        return (tNodoArbol**)p;
    return menorNodo(&(*p)->izq);
}

tNodoArbol** buscarNodo(tArbolBinBusq* p, const void* d, int(*cmp)(const void*, const void*))
{
    int rc;
    if(!*p)
        return NULL;
    if(*p && (rc = cmp(d,(*p)->info)))
    {
        if(rc < 0)
            return buscarNodo(&(*p)->izq,d,cmp);
        return buscarNodo(&(*p)->der,d,cmp);
    }
    return (tNodoArbol**)p;
}
int buscarElem( tArbolBinBusq* p, void* d, unsigned tam, int(*cmp)(const void*, const void*))
{
    if(!(p = buscarNodo(p,d,cmp)))
        return 0;
    memcpy(d, (*p)->info, minimo(tam,(*p)->tamInfo));
    return 1;
}

int eliminarElem(tArbolBinBusq* p,  void* d, unsigned tam, int(*cmp)(const void*, const void*))
{
    if(!(p = buscarNodo(p,d,cmp)))
        return 0;
    memcpy(d,(*p)->info, minimo(tam,(*p)->tamInfo));
    return eliminarRaiz(p);
}


int alturaArbol( tArbolBinBusq* p)
{
    if(!*p)
        return 0;
    int hi;
    int hd;
    hi = alturaArbol(&(*p)->izq);
    hd = alturaArbol(&(*p)->der);
    return (hi > hd ? hi : hd) + 1;
}

int generarConsulta(tArbolBinBusq* p, FILE* arch)
{
    tCola ColaConsultas;
    crearColaMia(&ColaConsultas);
    rewind(arch);
    int op;
    do
    {
        Consulta consulta;
        int nroCliente;
        float monto;
        printf("\nIngrese el nro de cliente:");
        scanf("%d",&nroCliente);
        consulta.nroPaciente = nroCliente;
        printf("\n Ingrese el monto:");
        scanf("%f", &monto);
        consulta.monto = monto;
        ponerEnColaMia(&ColaConsultas, &consulta, sizeof(Consulta));

        printf("\nDesea ingresar otra consulta? 1 para si 0 para no");
        scanf("%d", &op);
    }while(op == 1);
    Consulta cons;

    while(sacarDeColaMia(&ColaConsultas,&cons,sizeof(Consulta)) == 1)
    {
        tPaciente paciente;
        Indice ind;
        ind.nroPaciente = cons.nroPaciente;
        if(buscarElem(p,&ind,sizeof(Indice),cmpInd) != 1)
        {
            printf("\nPaciente %d no encontrado", ind.nroPaciente);
        }
        fseek(arch,ind.nroReg * sizeof(tPaciente),SEEK_SET);
        fread(&paciente,sizeof(tPaciente),1,arch);
        paciente.montoInvertido += cons.monto;
        paciente.cantidadConsultas++;
        fseek(arch,ind.nroReg * sizeof(tPaciente),SEEK_SET);
        fwrite(&paciente,sizeof(tPaciente),1, arch);
    }
    return 1;
}



void crearColaMia(tCola* p)
{
    p->pri = NULL;
    p->ult = NULL;
}

int ponerEnColaMia(tCola* p, const void* d, unsigned cantBytes)
{
    tNodo* nue;
    if((nue = malloc(sizeof(tCola))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    if(p->ult)
        p->ult->sig = nue;
    else
        p->pri = nue;
    p->ult = nue;
    return 1;
}

int sacarDeColaMia(tCola* p, void* d, unsigned cantBytes)
{
    tNodo* aux = p->pri;
    if(aux == NULL)
        return 0;
    p->pri = aux->sig;
    memcpy(d, aux->info, minimo(aux->tamInfo, cantBytes));
    free(aux->info);
    free(aux);
    if(p->pri == NULL)
        p->ult = NULL;
    return 1;
}




