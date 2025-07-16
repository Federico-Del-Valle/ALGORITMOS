int insertarRecArbolBinBusq(ArbolBinBusq* p, const void* d, unsigned tam,
                         int(*cmp)(const void*, const void*))
{
    NodoArbol* nue;
    int rc;

    while(*p)
    {
        if((rc = cmp(d, (*p)->info)) < 0)
            return insertarRecArbolBinBusq(&(*p)->izq, d, tam, cmp);
        else if (rc > 0)
            return insertarRecArbolBinBusq(&(*p)->der, d, tam, cmp);
        else
            return CLA_DUP;
    }
    if((nue = malloc(sizeof(NodoArbol))) == NULL ||
       (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);
    nue->der = nue->izq = NULL;
    *p = nue;
    return TODO_OK;
}
