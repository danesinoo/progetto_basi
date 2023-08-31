-- how much is earned by each category of products

SELECT p.tag, sum(p.prezzo * c.quantita) as totale
FROM prodotto as p, contenuto as c, ordine as o
WHERE p.id = c.prodotto
AND o.lista = c.lista
GROUP BY p.tag
HAVING sum(p.prezzo * c.quantita) > 100
ORDER BY totale DESC;
