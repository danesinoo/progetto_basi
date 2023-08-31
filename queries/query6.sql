-- guadagno totale per ogni giorno

SELECT DATE(data_creazione) AS day, sum(totale)
FROM lista, (
	SELECT ordine.lista, sum(prodotto.prezzo * contenuto.quantita) AS totale
	FROM ordine, prodotto, contenuto
	WHERE ordine.lista = contenuto.lista
	AND prodotto.id = contenuto.prodotto
	GROUP BY ordine.lista) as costo_ordini
WHERE lista.id = lista
GROUP BY day;
