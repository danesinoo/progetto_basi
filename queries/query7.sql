-- guadagno totale per ogni mese

SELECT EXTRACT(YEAR from data_creazione) AS year, EXTRACT(MONTH from data_creazione) AS month, sum(totale)
FROM lista, (
	SELECT ordine.lista, sum(prodotto.prezzo * contenuto.quantita) AS totale
	FROM ordine, prodotto, contenuto
	WHERE ordine.lista = contenuto.lista
	AND prodotto.id = contenuto.prodotto
	GROUP BY ordine.lista) AS costo_ordini
WHERE lista.id = lista
GROUP BY year, month
ORDER BY year, month;

