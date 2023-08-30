-- carrelli creati (liste) ma non processati come ordini

SELECT email, count(email) FROM ((SELECT utente.email, lista.id from utente, lista
WHERE utente.email = lista.utente) as tab
			   left outer join ordine
				on tab.id = ordine.lista)
				WHERE lista IS NULL
				GROUP BY email
