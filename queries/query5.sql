-- nome carrello e costo totale

SELECT nome, totale
FROM (
SELECT lista, sum(prezzo * quantita) as totale
FROM (SELECT lista.id, lista.nome, prodotto.prezzo, contenuto.quantita
FROM lista, prodotto, contenuto
WHERE lista.id = contenuto.lista
AND prodotto.id = contenuto.prodotto) as tab 
JOIN ordine
ON id = lista
GROUP BY lista
HAVING lista IS NULL) as tab, lista
WHERE tab.lista = lista.id
