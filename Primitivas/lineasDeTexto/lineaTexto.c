#include "lineaTexto.h"

int ingresarTexto(char* linea, int tamLinea)
{
    static const char* texto[] =
    {
        "Flaca - Andres Calamaro",
        "",
        "Flaca",
        "No me claves",
        "Tus puniales",
        "Por la espalda",
        "Tan profundo",
        "No me duelen",
        "No me hacen mal",
        "",
        "Lejos",
        "En el centro",
        "De la tierra",
        "Las raices",
        "Del amor",
        "Donde estaban",
        "Quedaran",
        "",
        "Entre el: No me olvides",
        "Me dejé nuestros abriles olvidados",
        "En el fondo del placar",
        "Del cuarto de invitados",
        "Eran tiempos dorados",
        "Un pasado mejor",
        "",
        "Aunque casi me equivoco",
        "Y te digo poco a poco",
        "No me mientas",
        "No me digas la verdad",
        "No te quedes callada",
        "No levantes la voz",
        "Ni me pidas perdon",
        "",
        "Aunque casi te confieso",
        "Que tambien he sido un perro companiero",
        "Un perro ideal que aprendio a ladrar",
        "Y a volver al hogar",
        "Para poder comer",
        "",
        "Flaca",
        "No me claves",
        "Tus puniales",
        "Por la espalda",
        "Tan profundo",
        "No me duelen",
        "No me hacen mal"
        "",
        NULL
    };

    static int posIni = 0;

    if(texto[posIni] == NULL)
    {
        posIni = 0;
        return 0;
    }

    *linea = '\0';
    strncat(linea, texto[posIni], tamLinea - 1);
    posIni++;

    return 1;
}

//Teniendo en cuenta que las lineas de texto no tienen '\n' al final
void mostrarLineasTextoTDA(const void* d, FILE* fp)
{
    fprintf(fp, "%s\n", (const char*)d);
}
