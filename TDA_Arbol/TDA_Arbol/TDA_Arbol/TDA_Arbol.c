#include"TDA_Arbol.h"

/// ========================================================================================================
/// Inicialización
/// ========================================================================================================
void crearArbol(tArbol* arbol)
{
    *arbol = NULL;
}

/// ========================================================================================================
///  Insertar
/// ========================================================================================================
int insArb(tArbol *arbol, void *info, size_t tamInfo, comparar cmp)
{
    tNodo *nue;
    int resCmp;

    // Recorremos iterativamente hasta la posición adecuada
    while(*arbol)
    {
        // Si es menor, va al subárbol izquierdo
        if((resCmp = cmp(info, (*arbol)->info)) < 0)
        {
            arbol = &(*arbol)->izq;
        }
        // Si es mayor, va al subárbol derecho
        else if(resCmp > 0)
        {
            arbol = &(*arbol)->der;
        }
        // Si es igual, no se inserta (no se permiten duplicados)
        else
        {
            return DUPLICADO;
        }
    }

    // Una vez llegada a la posición, creamos e insertamos el nodo
    if(!(nue = malloc(sizeof(tNodo))))
    {
        return SIN_MEM;
    }

    if(!(nue->info = malloc(tamInfo)))
    {
        free(nue);
        return SIN_MEM;
    }

    // Guardamos la información en el nuevo nodo
    nue->tamInfo = tamInfo;
    memcpy(nue->info, info, tamInfo);

    // Inicializamos los hijos como NULL
    nue->izq = NULL;
    nue->der = NULL;

    // Enlazamos el nuevo nodo al árbol
    *arbol = nue;

    return EXITO;
}

int rinsArb(tArbol *arbol, void *info, size_t tamInfo, comparar cmp)
{
    tNodo *nue;
    int resCmp;

    // Recorremos iterativamente hasta la posición adecuada
    if(*arbol)
    {
        // Si es menor, va al subárbol izquierdo
        if((resCmp = cmp(info, (*arbol)->info)) < 0)
        {
            return rinsArb(&(*arbol)->izq, info, tamInfo, cmp);
        }
        // Si es mayor, va al subárbol derecho
        else if(resCmp > 0)
        {
            return rinsArb(&(*arbol)->der, info, tamInfo, cmp);
        }
        // Si es igual, no se inserta (no se permiten duplicados)
        else
        {
            return DUPLICADO;
        }
    }

    // Una vez llegada a la posición, creamos e insertamos el nodo
    if(!(nue = malloc(sizeof(tNodo))))
    {
        return SIN_MEM;
    }

    if(!(nue->info = malloc(tamInfo)))
    {
        free(nue);
        return SIN_MEM;
    }

    // Guardamos la información en el nuevo nodo
    nue->tamInfo = tamInfo;
    memcpy(nue->info, info, tamInfo);

    // Inicializamos los hijos como NULL
    nue->izq = NULL;
    nue->der = NULL;

    // Enlazamos el nuevo nodo al árbol
    *arbol = nue;

    return EXITO;
}

// A diferencia de una inserción segura, esta versión no copia la información: simplemente guarda el puntero tal como viene.
int insDirArb(tArbol *arbol, void *info, size_t tamInfo, comparar cmp)
{
    int rc;

    // Recorremos iterativamente hasta la posición adecuada
    while (*arbol)
    {
        if ((rc = cmp(info, (*arbol)->info)) < 0)
        {
            arbol = &(*arbol)->izq;
        }
        else if (rc > 0)
        {
            arbol = &(*arbol)->der;
        }
        else
        {
            return DUPLICADO;
        }
    }

    tNodo *nue;

    if (!(nue = malloc(sizeof(tNodo))))
    {
        return SIN_MEM;
    }

    nue->tamInfo = tamInfo;
    nue->info = info;

    // Inicializamos los hijos como NULL
    nue->der = NULL;
    nue->izq = NULL;

    // Enlazamos el nuevo nodo al árbol
    *arbol = nue;

    return EXITO;
}

/// ========================================================================================================
/// Recorridos
/// ========================================================================================================
void _mapPre(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel)
{
     // Si el árbol está vacío (llegamos a una rama que no existe), salimos sin hacer nada.
    if(!*arbol)
        return;
    /* R */accion((*arbol)->info,(*arbol)->tamInfo,nivel,param); // Actual
    /* I */_mapPre(&(*arbol)->izq,accion,param,nivel+1); // Hijo izquierdo
    /* D */_mapPre(&(*arbol)->der,accion,param,nivel+1); // Hijo derecho
}
void mapPre(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param)
{
    _mapPre(arbol,accion,param,0);
}

void _mapIn(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel)
{
     // Si el árbol está vacío (llegamos a una rama que no existe), salimos sin hacer nada.
    if(!*arbol)
        return;

    /* I */_mapIn(&(*arbol)->izq,accion,param,nivel+1); // Hijo izquierdo
    /* R */accion((*arbol)->info,(*arbol)->tamInfo,nivel,param); // Actual
    /* D */_mapIn(&(*arbol)->der,accion,param,nivel+1); // Hijo derecho
}
void mapIn(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param)
{
    _mapIn(arbol,accion,param,0);
}

void _mapPos(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel)
{
     // Si el árbol está vacío (llegamos a una rama que no existe), salimos sin hacer nada.
    if(!*arbol)
        return;

    /* I */_mapPos(&(*arbol)->izq,accion,param,nivel+1); // Hijo izquierdo
    /* D */_mapPos(&(*arbol)->der,accion,param,nivel+1); // Hijo derecho
    /* R */accion((*arbol)->info,(*arbol)->tamInfo,nivel,param); // Actual
}
void mapPos(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param)
{
    _mapPos(arbol, accion, param, 0);
}

void _mapPreInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel)
{
     // Si el árbol está vacío (llegamos a una rama que no existe), salimos sin hacer nada.
    if(!*arbol)
        return;
    /* R */accion((*arbol)->info,(*arbol)->tamInfo,nivel,param); // Actual
    /* D */_mapPreInv(&(*arbol)->der,accion,param,nivel+1); // Hijo derecho
    /* I */_mapPreInv(&(*arbol)->izq,accion,param,nivel+1); // Hijo izquierdo
}
void mapPreInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param)
{
    _mapPreInv(arbol,accion,param,0);
}

void _mapInInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel)
{
     // Si el árbol está vacío (llegamos a una rama que no existe), salimos sin hacer nada.
    if(!*arbol)
        return;

    /* D */_mapInInv(&(*arbol)->der,accion,param,nivel+1); // Hijo derecho
    /* R */accion((*arbol)->info,(*arbol)->tamInfo,nivel,param); // Actual
    /* I */_mapInInv(&(*arbol)->izq,accion,param,nivel+1); // Hijo izquierdo
}
void mapInInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param)
{
    _mapInInv(arbol,accion,param,0);
}

void _mapPosInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param, size_t nivel)
{
     // Si el árbol está vacío (llegamos a una rama que no existe), salimos sin hacer nada.
    if(!*arbol)
        return;

    /* D */_mapPosInv(&(*arbol)->der,accion,param,nivel+1); // Hijo derecho
    /* I */_mapPosInv(&(*arbol)->izq,accion,param,nivel+1); // Hijo izquierdo
    /* R */accion((*arbol)->info,(*arbol)->tamInfo,nivel,param); // Actual
}
void mapPosInv(tArbol *arbol, void accion(void*,size_t,size_t,void*), void *param)
{
    _mapPosInv(arbol, accion, param, 0);
}

/// ========================================================================================================
/// Conteos y estadísticas del Arbol
/// ========================================================================================================

size_t alturaArbol(tArbol *arbol)
{
    // Caso base: si el árbol o rama está vacío, la altura es 0
    if(!*arbol)
    {
        return 0;
    }

    // La altura del arbol esta determinado por:
    // - El maximo entre el sub arbol izquierdo y derecho
    // - Se le suma 1 por cada nivel
    return MAX(alturaArbol(&(*arbol)->izq), alturaArbol(&(*arbol)->der)) + 1;
}

int esCompletoHastaNivelArbol(tArbol *arbol, size_t n)
{
    if(!*arbol)
    {
        return n < 0;
    }

    if(!n)
    {
        return 1;
    }

    return esCompletoHastaNivelArbol(&(*arbol)->izq, n-1) && esCompletoHastaNivelArbol(&(*arbol)->der, n-1);
}
int esCompletoArbol(tArbol *arbol)
{
    return esCompletoHastaNivelArbol(arbol, alturaArbol(arbol)-1);
}

int esBalanceadoArbol(tArbol *arbol)
{
    return esCompletoHastaNivelArbol(arbol, alturaArbol(arbol) - 2);
}

/*
1. Recorre el árbol recursivamente.
2. Calcula la altura de cada subárbol izquierdo (hi) y derecho (hd).
3. Si la diferencia de alturas es mayor a 1, retorna 0 (no es AVL).
4. Si no, sigue verificando recursivamente en ambos subárboles.
*/
int esAVLArbol(tArbol *arbol)
{
    if (!*arbol)
    {
        return 1;
    }

    size_t hi = alturaArbol( &(*arbol)->izq );
    size_t hd = alturaArbol( &(*arbol)->der );

    if (abs(hi - hd) > 1)
    {
        return 0;
    }

    return esAVLArbol( &(*arbol)->izq ) && esAVLArbol( &(*arbol)->der );
}


/// ========================================================================================================
/// Conteos y estadísticas de los Nodos
/// ========================================================================================================
size_t cantNodosArbol(tArbol *arbol)
{
    // Caso base: si el árbol está vacío, no hay nodos
    if(!*arbol)
        return 0;

    // Caso recursivo:
    // - Cuenta los nodos del subárbol izquierdo
    // - Cuenta los nodos del subárbol izquierdo
    // - suma 1 por el nodo actual
    return cantNodosArbol(&(*arbol)->izq)+cantNodosArbol(&(*arbol)->der)+1;
}

size_t cantHojasArbol(tArbol* arbol)
{
     // Caso base: árbol vacío ⇒ no hay hojas
    if (!*arbol)
        return 0;

    // Si el nodo actual no tiene hijos, es una hoja
    if ((*arbol)->izq == NULL && (*arbol)->der == NULL)
        return 1;

    // Caso general: sumar hojas del subárbol izquierdo y derecho
    return cantHojasArbol(&(*arbol)->izq) + cantHojasArbol(&(*arbol)->der);
}

size_t cantNoHojasArbol(tArbol* arbol)
{
    // Caso base: árbol vacío ⇒ no hay hojas
    if (!*arbol)
        return 0;

    // Si el nodo actual tiene al menos un hijo, es no-hoja
    if ((*arbol)->izq || (*arbol)->der)
        return 1 + cantNoHojasArbol(&(*arbol)->izq) + cantNoHojasArbol(&(*arbol)->der);

    // Si no tiene hijos, no sumamos, solo seguimos recursión
    return 0;
}

size_t cantNodosHastaNivel(tArbol* arbol, size_t nivel)
{
    // Si el árbol está vacío
    if (!*arbol)
        return 0;

    // Contar el nodo actual
    if(!nivel)
        return 1;

    // Contar el nodo actual + nodos de subárboles con nivel reducido
    return 1 +
           cantNodosHastaNivel(&(*arbol)->izq, nivel - 1) +
           cantNodosHastaNivel(&(*arbol)->der, nivel - 1);
}

size_t cantNodosEnNivel(tArbol* arbol, size_t nivel)
{
    // Se llama a la función recursiva auxiliar con nivelActual = 0 (raíz)
    return _cantNodosEnNivel(arbol, 0, nivel);
}
size_t _cantNodosEnNivel(tArbol* arbol, size_t nivelActual, size_t nivelObjetivo)
{
    // Si el árbol está vacío, no hay nodos para contar
    if (!*arbol)
        return 0;

    // Si estamos en el nivel objetivo, este nodo cuenta como uno
    if (nivelActual == nivelObjetivo)
        return 1;

    // sumar los nodos en los subárboles izquierdo y derecho
    // aumentando el nivel actual en cada llamada
    return _cantNodosEnNivel(&(*arbol)->izq, nivelActual + 1, nivelObjetivo) +
           _cantNodosEnNivel(&(*arbol)->der, nivelActual + 1, nivelObjetivo);
}

size_t cantNodosAPartirDeNivel(tArbol* arbol, size_t nivel)
{
    return _cantNodosAPartirDeNivel(arbol, 0, nivel);
}
size_t _cantNodosAPartirDeNivel(tArbol* arbol, size_t nivelActual, size_t nivelObjetivo)
{
    if (!*arbol)
        return 0;

    // Si el nivel actual es mayor o igual al objetivo, contar este nodo
    size_t cont = nivelActual >= nivelObjetivo ? 1 : 0;

    // Sumar recursivamente los nodos de los subárboles izquierdo y derecho
    return cont
           + _cantNodosAPartirDeNivel(&(*arbol)->izq, nivelActual + 1, nivelObjetivo)
           + _cantNodosAPartirDeNivel(&(*arbol)->der, nivelActual + 1, nivelObjetivo);
}

size_t cantHijosIzq(tArbol* arbol)
{
    if(!*arbol)
        return 0;

    int cont = (*arbol)->izq ? 1 : 0;

    return cantHijosIzq(&(*arbol)->izq)+
           cantHijosIzq(&(*arbol)->der)+
           cont;
}

size_t cantHijosSoloIzq(tArbol* arbol)
{
    if (!*arbol)
        return 0;

    // Verificamos si tiene hijo izquierdo y NO tiene hijo derecho
    int soloIzq = ((*arbol)->izq != NULL && (*arbol)->der == NULL) ? 1 : 0;

    // Sumamos en ambos subárboles
    return soloIzq +
           cantHijosSoloIzq(&(*arbol)->izq) +
           cantHijosSoloIzq(&(*arbol)->der);
}

/// ========================================================================================================
/// Búsqueda
/// ========================================================================================================
//Busca un nodo en un árbol binario de búsqueda que coincida con una clave dada.
tArbol* busqNodoArbol(tArbol* arbol, void* clave, comparar cmp)
{
    if (!*arbol)
        return NULL;  // Árbol vacío o no se encontró la clave

    int resCmp = cmp(clave, (*arbol)->info);

    if (resCmp < 0)
        return busqNodoArbol(&(*arbol)->izq, clave, cmp);  // Buscar en subárbol izquierdo

    if (resCmp > 0)
        return busqNodoArbol(&(*arbol)->der, clave, cmp);  // Buscar en subárbol derecho

    return arbol;  // resCmp == 0 → se encontró la clave
}

// Busca un elemento en un árbol binario de búsqueda y copia su contenido si lo encuentra.
int busqElemArbol(tArbol* arbol, void* destino, size_t tamDestino, comparar cmp)
{
    if (!(arbol = busqNodoArbol(arbol, destino, cmp)))
    {
        return NO_ENCONTRADO;
    }

    memcpy(destino, (*arbol)->info, MIN(tamDestino, (*arbol)->tamInfo));

    return EXITO;
}

/// ========================================================================================================
/// SubArbol
/// ========================================================================================================
//La función cantNodosSubArbol sirve para contar cuántos nodos hay en un subárbol a partir de un nodo cuya clave coincide con la buscada.
size_t cantNodosSubArbol(tArbol* arbol, void* clave, comparar cmp)
{
    if(!(arbol = busqNodoArbol(arbol, clave, cmp)))
    {
        return 0;
    }
    return cantNodosArbol(arbol);
}

/// ========================================================================================================
/// Eliminación
/// ========================================================================================================
// Elimina un nodo solo si es una hoja
int eliminarHoja(tArbol* arbol, void* claveHoja, comparar cmp)
{
    tArbol* pHoja = busqNodoArbol(arbol, claveHoja, cmp); // Busca la dirección al nodo con la clave

    if (!*pHoja)
        return NO_ENCONTRADO; // No existe la clave buscada

    if ((*pHoja)->izq != NULL || (*pHoja)->der != NULL)
        return NO_ES_HOJA; // El nodo tiene al menos un hijo → no es hoja

    free((*pHoja)->info); // Libera la información
    free(*pHoja);         // Libera el nodo
    *pHoja = NULL;        // Deja el puntero en NULL

    return EXITO;
}

/*
1. Si el puntero está vacío → retorna NO_ENCONTRADO.
2. Libera la info del nodo raíz.
3. Si la raíz es una hoja → la libera y deja el puntero en NULL.
4. Si tiene hijos, elige el reemplazo según la altura de los subárboles:
    - Si el izquierdo es más alto → reemplaza con el mayor del subárbol izquierdo.
    - Si el derecho es más alto →   reemplaza con el menor del subárbol derecho.
5. Copia los datos del nodo de reemplazo a la raíz.
6. Conecta los hijos del nodo reemplazo (si los hay) en su lugar original.
7. Libera el nodo reemplazo.
*/
int eliminarRaiz(tArbol* arbol)
{
    /// 1. Si el puntero está vacío → retorna NO_ENCONTRADO.
    if(!*arbol)
    {
        return NO_ENCONTRADO;
    }

    /// 2. Libera la info del nodo raíz.
    free((*arbol)->info); ///Liberamos la info de la raiz

    /// 3. Si la raíz es una hoja → la libera y deja el puntero en NULL.
    if(!(*arbol)->izq && !(*arbol)->der)
    {
        free(*arbol);
        *arbol = NULL;
        return EXITO;
    }

    /// 4. Si tiene hijos, elige el reemplazo según la altura de los subárboles:
    // - Si el izquierdo es más alto → reemplaza con el mayor del subárbol izquierdo.
    // - Si el derecho es más alto →   reemplaza con el menor del subárbol derecho.
    tArbol* remp, elim;

    remp = alturaArbol(&(*arbol)->izq) > alturaArbol(&(*arbol)->der) ? busqNodoMaxArbol(&(*arbol)->izq) : busqNodoMinArbol(&(*arbol)->der);
    elim = *remp;

    ///5. Copia los datos del nodo de reemplazo a la raíz.
    (*arbol)->info = elim->info;
    (*arbol)->tamInfo = elim->tamInfo;

    /// 6. Conecta los hijos del nodo reemplazo (si los hay) en su lugar original.
    *remp = elim->izq ? elim->izq : elim->der;

    /// 7. Libera el nodo reemplazo.
    free(elim);
    return EXITO;
}

// Elimina un nodo
int eliminarNodo(tArbol* arbol, void* clave, comparar cmp)
{
    if (!(arbol = busqNodoArbol(arbol, clave, cmp)))
    {
        return NO_ENCONTRADO;
    }

    return eliminarRaiz(arbol);
}

/// ========================================================================================================
/// Mínimo y Máximo
/// ========================================================================================================
// El mayor elemento siempre está en la rama más a la derecha.
// Esta función recorre recursivamente por la rama derecha hasta que no encuentra más hijos derechos.
tArbol* busqNodoMaxArbol(tArbol *arbol)
{
    // Arbol Vacio
    if(!*arbol)
    {
        return NULL;
    }

    // Ultimo Nodo
    if(!(*arbol)->der)
    {
        return arbol;
    }

    // Retornamos Recursivo
    return busqNodoMaxArbol(&(*arbol)->der);
}

tArbol* busqNodoMinArbol(tArbol *arbol)
{
    // Arbol Vacio
    if(!*arbol)
    {
        return NULL;
    }

    // Ultimo Nodo
    if(!(*arbol)->izq)
    {
        return arbol;
    }

    // Retornamos Recursivo
    return busqNodoMinArbol(&(*arbol)->izq);
}

int busqElemMaxArbol(tArbol *arbol, void *info, size_t tamInfo)
{
    if(!(arbol = busqNodoMaxArbol(arbol)))
    {
        return ARBOL_VACIO;
    }

    memcpy(info, (*arbol)->info, MIN(tamInfo, (*arbol)->tamInfo));

    return EXITO;
}

int busqElemMinArbol(tArbol *arbol, void *info, size_t tamInfo)
{
    if(!(arbol = busqNodoMinArbol(arbol)))
    {
        return ARBOL_VACIO;
    }

    memcpy(info, (*arbol)->info, MIN(tamInfo, (*arbol)->tamInfo));

    return EXITO;
}

/// ========================================================================================================
/// Limpieza
/// ========================================================================================================
void eliminarArbol(tArbol* arbol)
{
    // Si el árbol está vacío, no hay nada que hacer
    if (!*arbol)
    {
        return;
    }

    /* I */ eliminarArbol( &(*arbol)->izq );
    /* D */ eliminarArbol( &(*arbol)->der );
    /* R */ free((*arbol)->info);
            free(*arbol);

    *arbol = NULL;
}

/// ========================================================================================================
/// Operaciones sin tener Clave
/// ========================================================================================================
tArbol* busqNodoMinNoClaveArbol(tArbol *arbol, comparar cmp)
{
    return _busqNodoMinNoClaveArbol(arbol, NULL, cmp);
}
tArbol* _busqNodoMinNoClaveArbol(tArbol *arbol, tArbol *min, comparar cmp)
{
    if(!*arbol)
    {
        return min;
    }

    if(!*min || cmp((*arbol)->info, (*min)->info) < 0)
    {
        min = arbol;
    }

    min = _busqNodoMinNoClaveArbol(&(*arbol)->izq, min, cmp);
    min = _busqNodoMinNoClaveArbol(&(*arbol)->der, min, cmp);

    return min;
}
int busqElemMinNoClaveArbol(tArbol *arbol, void *info, size_t tamInfo, comparar cmp)
{
    if(!(arbol = busqNodoMinNoClaveArbol(arbol, cmp)))
    {
        return NO_ENCONTRADO;
    }

    memcpy(info, (*arbol)->info, MIN(tamInfo, (*arbol)->tamInfo));

    return EXITO;
}

tArbol* busqNodoMaxNoClaveArbol(tArbol *arbol, comparar cmp)
{
    return _busqNodoMaxNoClaveArbol(arbol, NULL, cmp);
}
tArbol* _busqNodoMaxNoClaveArbol(tArbol *arbol, tArbol *max, comparar cmp)
{
    if(!*arbol)
    {
        return max;
    }

    if(!*max || cmp((*arbol)->info, (*max)->info) > 0)
    {
        max = arbol;
    }

    max = _busqNodoMaxNoClaveArbol(&(*arbol)->izq, max, cmp);
    max = _busqNodoMaxNoClaveArbol(&(*arbol)->der, max, cmp);

    return max;
}
int busqElemMaxNoClaveArbol(tArbol *arbol, void *info, size_t tamInfo, comparar cmp)
{
    if(!(arbol = busqNodoMaxNoClaveArbol(arbol, cmp)))
    {
        return NO_ENCONTRADO;
    }

    memcpy(info, (*arbol)->info, MIN(tamInfo, (*arbol)->tamInfo));

    return EXITO;
}

tArbol* busqNodoNoClaveArbol(tArbol* arbol, void* info, comparar cmp)
{
    if(!*arbol)
    {
        return NULL;
    }

    if(cmp((*arbol)->info, info) == 0)
    {
        return arbol;
    }

    tArbol *busq = busqNodoNoClaveArbol(&(*arbol)->der, info, cmp);

    return  busq ? busq : busqNodoNoClaveArbol(&(*arbol)->izq, info, cmp);
}
int busqElemNoClaveArbol(tArbol* arbol, void* destino, size_t tamDestino, comparar cmp)
{
    if(!(arbol = busqNodoNoClaveArbol(arbol, destino, cmp)))
    {
        return NO_ENCONTRADO;
    }

    memcpy(destino, (*arbol)->info, MIN(tamDestino, (*arbol)->tamInfo));

    return EXITO;
}

void eliminarNodoNoClaveArbol(tArbol *arbol, void *info, comparar cmp)
{
    if(!*arbol)
    {
        return;
    }

    eliminarNodoNoClaveArbol(&(*arbol)->izq, info, cmp);
    eliminarNodoNoClaveArbol(&(*arbol)->der, info, cmp);

    if(!cmp(info, (*arbol)->info))
    {
        eliminarRaiz(arbol);
    }
}

