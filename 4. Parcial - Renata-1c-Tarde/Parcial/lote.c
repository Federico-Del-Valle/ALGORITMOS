
inr compararPorIdProducto(const void* a, const void* b)
{
    const Lote* lote1 = (const Lote*)a;
    const Lote* lote2 = (const Lote*)b;

    return lote1->idCod - lote2->idCod;
}
