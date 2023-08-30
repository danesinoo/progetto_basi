-- quanti ordini sono stati fatti da ogni singolo utente in un determinato intervallo temporale

SELECT utente.email, count(utente.email)
FROM utente, lista, ordine
WHERE utente.email = lista.utente
AND lista.id = ordine.lista
GROUP BY (utente.email)
