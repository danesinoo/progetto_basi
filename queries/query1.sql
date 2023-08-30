-- quanti prodotti sono stati comprati da ogni utente in un determinato intervallo temporale
SELECT lista.utente, sum(contenuto.quantita)
FROM lista, contenuto
WHERE lista.id = contenuto.lista AND lista.data_creazione > '2023-01-01'
GROUP BY (lista.utente);
