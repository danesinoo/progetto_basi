-- numero ordine e costo totale

SELECT lista.id, totale
from lista, (select ordine.lista, sum(prodotto.prezzo * contenuto.quantita) as totale
FROM ordine, prodotto, contenuto
WHERE ordine.lista = contenuto.lista
AND prodotto.id = contenuto.prodotto
GROUP BY ordine.lista) as costo_ordini
WHERE lista.id = lista