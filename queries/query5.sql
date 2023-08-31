-- nome carrello e costo totale

SELECT lista.nome, totale 
FROM (SELECT tab.id, sum(prezzo * quantita) as totale
	FROM (SELECT lista.id as id, prodotto.prezzo, contenuto.quantita
		FROM lista, prodotto, contenuto
		WHERE lista.id = contenuto.lista
		AND prodotto.id = contenuto.prodotto
	) as tab LEFT JOIN ordine
	ON tab.id = lista
	WHERE indirizzo is NULL
	GROUP BY tab.id) as tab2, lista
WHERE tab2.id = lista.id;
