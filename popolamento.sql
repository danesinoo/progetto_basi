--  POPOLAMENTO DELLE TABELLE

INSERT INTO utente (email, password, nome, cognome) VALUES
('mauro.cattaneo@gmail.com', 'password', 'Mauro', 'Cattaneo'),
('arturo.rizzo@gmail.com', 'password', 'arturo', 'rizzo'),
('sandro.schiavone@gmail.com', 'password', 'sandro', 'schiavone'),
('mauro.giordano@gmail.com', 'password', 'mauro', 'giordano'),
('cristiano.giordano@gmail.com', 'password', 'cristiano', 'giordano'),
('lavinia.toscano@gmail.com', 'password', 'lavinia', 'toscano'),
('miriam.angelo@gmail.com', 'password', 'miriam', 'angelo'),
('leila.costa@gmail.com', 'password', 'leila', 'costa'),
('melania.calabrese@gmail.com', 'password', 'melania', 'calabrese'),
('arianna.palermo@gmail.com', 'password', 'arianna', 'palermo');

INSERT INTO carta_di_credito (numero, intestatario, scadenza, cvv, utente) VALUES
('4619859532357609', 'Mauro Cattaneo', '2026-01-01', '443', 'mauro.cattaneo@gmail.com'),
('4694038576505583', 'Arturo Rizzo', '2025-10-01', '057', 'arturo.rizzo@gmail.com'),
('4822293516814513', 'Sandro Schiavone', '2027-11-01', '447', 'sandro.schiavone@gmail.com'),
('4280794322027690', 'Mauro Giordano', '2026-08-01', '485', 'mauro.giordano@gmail.com'),
('4119865677385466', 'Cristiano Giordano', '2026-08-01', '212', 'cristiano.giordano@gmail.com'),
('4365747884217099', 'Lavinia Toscano', '2024-07-01', '290', 'lavinia.toscano@gmail.com'),
('4268601990913463', 'Miriam Angelo', '2028-01-01', '441', 'miriam.angelo@gmail.com'),
('4784837462867218', 'Leila Costa', '2028-02-01', '755', 'leila.costa@gmail.com'),
('4991830720961864', 'Melania Calabrese', '2025-01-01', '502', 'melania.calabrese@gmail.com'),
('4022707262300912', 'Arianna Palermo', '2026-09-01', '801', 'arianna.palermo@gmail.com');

INSERT INTO indirizzo (via, numero_civico, cap, citta, stato) VALUES
('Borgo Marianita', 0, '18555', 'Quarto Enzo', 'IT'),
('Rotonda Grasso', 3, '56927', 'Perugia', 'IT'),
('Contrada Gilda', 274, '07196', 'Settimo Sibilla Taranto', 'IT'),
('Via Longo', 7, '24972', 'Sibilla Ligure Ascoli Piceno', 'IT'),
('Rotonda Donati', 878, '83908', 'De Luca Calabro Rimini', 'IT'),
('Contrada Farina', 0, '29268', 'Quarto Rudy Terme Cagliari', 'IT'),
('Strada Giulietta', 764, '66241', 'Palmieri Sardo Palermo', 'IT'),
('Piazza Giovanna', 5, '78711', 'Guerra A Mare Siracusa', 'IT'),
('Via Sartori', 7, '31777', 'Lino Umbro Ferrara', 'IT'),
('Rotonda Deborah', 199, '24900', 'Quarto Fiorentino Sardo Sassari', 'IT'),
('Via Castellana', 100, '31060', 'Resana', 'IT');

-- da popolare in un secondo momento.
INSERT INTO lista (nome, utente, data_creazione, data_modifica) VALUES 
('carrello mauro', 'mauro.cattaneo@gmail.com', '2022-08-09', '2022-08-09'),
('carrello arturo', 'arturo.rizzo@gmail.com', '2022-09-09', '2022-09-09'),
('carrello sandro', 'sandro.schiavone@gmail.com', '2022-08-19', '2022-08-19'),
('carrello mauro', 'mauro.giordano@gmail.com', '2022-08-19', '2022-08-19'),
('carrello cristiano', 'cristiano.giordano@gmail.com', '2022-08-21', '2022-08-22'),
('carrello lavinia', 'lavinia.toscano@gmail.com', '2022-09-19', '2022-09-19'),
('carrello lavinia', 'lavinia.toscano@gmail.com', '2023-01-10', '2023-01-10'),
('carrello miriam', 'miriam.angelo@gmail.com', '2023-02-20', '2023-02-20'),
('carrello melania calabrese', 'melania.calabrese@gmail.com', '2023-02-20', '2023-02-20');

INSERT INTO categoria (nome, descrizione) VALUES
('Scarpe da trekking', 'descrizione'),
('Zaini da montagna', 'descrizione'), 
('Felpe', 'descrizione'), 
('Tute da sci', 'descrizione');

