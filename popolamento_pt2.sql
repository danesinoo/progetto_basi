-- seconda parte popolamento.
INSERT INTO indirizzo_spedizione (utente, indirizzo) VALUES
('mauro.cattaneo@gmail.com', 1),
('mauro.cattaneo@gmail.com', 11),
('arturo.rizzo@gmail.com', 2),
('sandro.schiavone@gmail.com', 3),
('mauro.giordano@gmail.com', 4),
('cristiano.giordano@gmail.com', 5),
('lavinia.toscano@gmail.com', 6),
('miriam.angelo@gmail.com', 7),
('leila.costa@gmail.com', 8),
('melania.calabrese@gmail.com', 9),
('arianna.palermo@gmail.com', 10);

INSERT INTO prodotto (nome, descrizione, prezzo, quantita, tag) VALUES 
('Scarpe trekking donna MH100 MID', 'scarpe da trekking', 60.99, 100, 'Scarpe da trekking'),
('Scarpe trekking uomo Columbia REDBUD TRANSALP', 'scarpe da trekking', 74.99, 100, 'Scarpe da trekking'),
('Scarpe trekking bambino Adidas HYPERHIKER LOW nere', 'scarpe da trekking', 29.99, 100, 'Scarpe da trekking'),
('Scarpe trekking uomo MH100 WTP', 'scarpe da trekking', 50.99, 100, 'Scarpe da trekking'),
('Giacca sci uomo 500 gialla e nera', 'tuta da sci da uomo', 129.99, 100, 'Tute da sci'),
('Giacca sci uomo 500 bianca', 'tuta da sci da uomo', 119.99, 100, 'Tute da sci'),
('Pantaloni sci donna 100 neri', 'tuta da sci da donna', 24.99, 100, 'Tute da sci'),
('Felpa pile Sport invernali Verde Cenere Uomo', 'felpa da uomo', 69.99, 100, 'Felpe'),
('Felpa pile Sport invernali Bianco panna Uomo', 'felpa da uomo', 49.99, 100, 'Felpe'),
('Felpa pile Sport invernali Verde Cenere Donna', 'felpa da donna', 69.99, 100, 'Felpe'),
('Felpa pile Sport invernali Bianco panna Donna', 'felpa da donna', 49.99, 100, 'Felpe'),
('Zaino trekking 20 L nero', 'zaino 20L', 12.99, 100, 'Zaini da montagna'),
('Zaino trekking 30L nero', 'zaino 30L', 19.99, 100, 'Zaini da montagna'),
('Zaino trekking 40L', 'zaino 42L', 75.99, 100, 'Zaini da montagna');

INSERT INTO ordine (lista, indirizzo, provider, status) VALUES
(1, 11, 'EClothMountain', 'effettuato'),
(2, 2, 'EClothMountain', 'effettuato'),
(3, 3, 'EClothMountain', 'effettuato'),
(4, 4, 'EClothMountain', 'effettuato'),
(5, 5, 'EClothMountain', 'effettuato'),
(6, 6, 'EClothMountain', 'spedito'),
(7, 6, 'EClothMountain', 'spedito'),
(8, 7, 'EClothMountain', 'spedito'),
(9, 9, 'EClothMountain', 'spedito');

