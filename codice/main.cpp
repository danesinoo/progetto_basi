#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "dependencies/libpq-fe.h"


#define PG_HOST "127.0.0.1" // oppure " localhost " o " postgresql "
#define PG_USER "postgres" // nome utente
#define PG_DB "EClothMountainDb" // nome database
#define PG_PASS "password" // nome password
#define PG_PORT 5432 // numero della porta

// firme metodi
void eliminazione_contenuto(PGconn* conn, std::string id_carrello);

void checkConnection(PGconn* conn) {
	if(PQstatus(conn) != CONNECTION_OK) {
		std::cout << "Errore di connessione " << PQerrorMessage(conn) << std::endl;
		PQfinish(conn);
		exit(1);
	} else {
		std::cout << "connessione avvenuta correttamente" << std::endl;
	}
}


void checkUpdateResults(PGresult* res, PGconn* conn) {

	// PGRES_TUPLES_OK,			/* a query command that returns tuples was
	// PGRES_COMMAND_OK
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Qualcosa è andato storto." << std::endl;
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
}

void print_results(PGresult* res) {
	int tuple = PQntuples(res);
	int campi = PQnfields(res);

	for(int i = 0; i < campi; i++) {
		std::cout << PQfname(res, i) << "\t\t";
	}
	
	std::cout << std::endl;

	for(int i = 0; i < tuple; i++) {
		for(int j = 0; j < campi; j++) {
			std::cout << PQgetvalue(res, i, j) << "\t\t";
		}
		std::cout << std::endl;
	}

}

void get_parameters(const std::vector<std::string>& msg, std::vector<std::string>& args) {
	std::string aux = "";
	for(auto cit = msg.begin(); cit != msg.end(); cit++) {
		std::cout << *cit;
		std::cin >> aux;
		args.push_back(aux);
		aux = "";
	}
}

void get_results(PGresult* res, std::vector<std::string>& vector) {
	int tuple = PQntuples(res);
	int campi = PQnfields(res);


	for(int i = 0; i < tuple; i++) {
		for(int j = 0; j < campi; j++) {
			std::stringstream aux;
			aux << PQgetvalue(res, i, j) << "\t\t";
			vector.push_back(aux.str());
		}
		// std::cout << std::endl;
	}
}

void checkSelectResults(PGresult* res, PGconn* conn) {

	// PGRES_TUPLES_OK,			/* a query command that returns tuples was
	// PGRES_COMMAND_OK     /* a query command that returns nothing
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::cout << "Qualcosa è andato storto." << std::endl;
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
}

void inserimento_utente(PGconn* conn) {

	// risultato
	PGresult* res;

	PGresult* stmt = PQprepare(conn, "inserimento_utente", "INSERT INTO utente (email, password, nome, cognome) VALUES ($1::varchar, $2::varchar, $3::varchar, $4::varchar)", 4, NULL);


	std::string email = "";
	std::string password = "";
	std::string nome = "";
	std::string cognome = "";

	std::cout << "IMMETTI INDIRIZZO E MAIL: ";
	std::cin >> email;
	
	std::cout << "IMMETTI PASSWORD : ";
	std::cin >> password;

	std::cout << "IMMETTI NOME: ";
	std::cin >> nome;

	std::cout << "IMMETTI COGNOME: ";
	std::cin >> cognome;

	const char* parameters[4] = {email.c_str(), password.c_str(), nome.c_str(), cognome.c_str()};
	// const char* parameter[2] = {nome.c_str(), email.c_str()};

	res = PQexecPrepared(conn, "inserimento_utente", 4, parameters, NULL, NULL, 0);
	
	checkUpdateResults(res, conn);
}

void inserimento_carta_di_credito(PGconn* conn) {
// risultato
	PGresult* res;

	PGresult* stmt = PQprepare(conn, "inserimento_carta_di_credito", "INSERT INTO carta_di_credito (numero, intestatario, scadenza, cvv, utente) VALUES ($1::varchar, $2::varchar, $3::date, $4::integer, $5::varchar)", 5, NULL);

	std::string numero = "";
	std::string intestatario = "";
	std::string scadenza = "";
	std::string cvv = "";
	std::string utente = "";


	std::cout << "IMMETTI NUMERO CARTA: ";
	std::cin >> numero;
	
	std::cout << "IMMETTI INTESTATARIO: ";
	std::cin >> intestatario;

	std::cout << "IMMETTI SCADENZA nel formato YYYY-MM-DD: ";
	std::cin >> scadenza;

	std::cout << "IMMETTI CVV: ";
	std::cin >> cvv;

	std::cout << "IMMETTI UTENTE: ";
	std::cin >> utente;

	const char* parameters[5] = {numero.c_str(), intestatario.c_str(), scadenza.c_str(), cvv.c_str(), utente.c_str()};

	res = PQexecPrepared(conn, "inserimento_carta_di_credito", 5, parameters, NULL, NULL, 0);
	
	checkUpdateResults(res, conn);
}

void inserimento_indirizzo(PGconn* conn) {
	
	PGresult* res;

	PGresult* stmt = PQprepare(conn, "inserimento_indirizzo", "INSERT INTO indirizzo (via, numero_civico, cap, citta, stato) VALUES ($1::varchar, $2::integer, $3::varchar, $4::varchar, $5::varchar)", 5, NULL);
	std::vector<std::string> array = {"IMMETTI VIA: ", 
		"IMMETTI NUMERO CIVICO: ",
		"IMMETTI CAP: ", 
		"IMMETTI CITTA: ", 
		"IMMETTI STATO: " };

	const char* parameters[5] = {"", "", "", "", ""};

	for(int i = 0; i < array.size(); i++) {
		std::string aux = "";
		std::cout << array[i];
		std::cin >> aux;
		std::cout << aux.c_str() << std::endl;
		parameters[i] = aux.c_str();
	}
	
	
	res = PQexecPrepared(conn, "inserimento_indirizzo", 5, parameters, NULL, NULL, 0);

	checkUpdateResults(res, conn);
}

void creazione_carrello(PGconn* conn) {

	PGresult* res;
	// ottenimento parametri
	std::vector<std::string> array = {"IMMETTI NOME: ", 
		"IMMETTI UTENTE: ",
		"IMMETTI DATA CREAZIONE: ", 
		"IMMETTI DATA MODIFICA: "
	};
	std::vector<std::string> v_aux;
	get_parameters(array, v_aux);

	// esecuzione query
	const char* parameters[4] = {v_aux[0].c_str(), v_aux[1].c_str(), v_aux[2].c_str(), v_aux[3].c_str(),};
	PGresult* stmt = PQprepare(conn, "creazione_carrello", "INSERT INTO lista (nome, utente, data_creazione, data_modifica) VALUES ($1::varchar, $2::varchar, $3::date, $4::date)", 4, NULL);
	res = PQexecPrepared(conn, "creazione_carrello", 4, parameters, NULL, NULL, 0);

	// controllo query
	checkUpdateResults(res, conn);
}

void eliminazione_carrello(PGconn* conn) {
	PGresult* res;

	// ottenimento parametri 
	std::vector<std::string> array = { 
		"IMMETTI ID CARRELLO", 
	};
	std::vector<std::string> v_aux;
	get_parameters(array, v_aux);

	eliminazione_contenuto(conn, v_aux[0]);

	// esecuzione query
	const char* parameters[1] = {v_aux[0].c_str()};
	PGresult* stmt = PQprepare(conn, "eliminazione_carrello", "DELETE FROM lista * WHERE id = $1::integer", 1, NULL);
	res = PQexecPrepared(conn, "eliminazione_carrello", 1, parameters, NULL, NULL, 0);

	// controllo query
	checkUpdateResults(res, conn);

}
void inserimento_contenuto(PGconn* conn) {

	PGresult* res;
	// ottenimento parametri
	std::vector<std::string> array = {"IMMETTI ID LISTA: ", 
		"IMMETTI ID PRODOTTO: ",
		"IMMETTI QUANTITA: "
	};
	std::vector<std::string> v_aux;
	get_parameters(array, v_aux);

	// esecuzione query
	const char* parameters[4] = {v_aux[0].c_str(), v_aux[1].c_str(), v_aux[2].c_str() };
	PGresult* stmt = PQprepare(conn, "inserimento_contenuto", "INSERT INTO contenuto (lista, prodotto, quantita) VALUES ($1::integer, $2::integer, $3::integer)", 3, NULL);
	res = PQexecPrepared(conn, "inserimento_contenuto", 3, parameters, NULL, NULL, 0);

	// controllo query
	checkUpdateResults(res, conn);
}

void eliminazione_contenuto(PGconn* conn, std::string id_carrello) {
	
	PGresult* res;
	
	// esecuzione query
	const char* parameters[1] = {id_carrello.c_str()};
	PGresult* stmt = PQprepare(conn, "eliminazione_contenuto", "DELETE FROM contenuto * WHERE lista = $1::integer", 1, NULL);
	res = PQexecPrepared(conn, "eliminazione_contenuto", 1, parameters, NULL, NULL, 0);

	// controllo query
	checkUpdateResults(res, conn);
}

void modifica_quantita_prodotto(PGconn* conn) {

	PGresult* res;
	// ottenimento parametri
	std::vector<std::string> array = {
		"IMMETTI QUANTITA: ",
		"IMMETTI ID PRODOTTO: "
	};
	std::vector<std::string> v_aux;
	get_parameters(array, v_aux);

	// esecuzione query
	const char* parameters[2] = {v_aux[0].c_str(), v_aux[1].c_str()};
	PGresult* stmt = PQprepare(conn, "modifica_quantita_prodotto", "UPDATE prodotto SET quantita = $1::integer WHERE id = $2::integer ", 2, NULL);
	res = PQexecPrepared(conn, "modifica_quantita_prodotto", 2, parameters, NULL, NULL, 0);

	// controllo query
	checkUpdateResults(res, conn);
}

void creazione_ordine(PGconn* conn) {
	PGresult* res;
	// ottenimento parametri
	std::vector<std::string> array = {"IMMETTI ID LISTA: ", 
		"IMMETTI ID INDIRIZZO: ",
		"IMMETTI PROVIDER: ",
		"IMMETTI STATUS: "
	};
	std::vector<std::string> v_aux;
	get_parameters(array, v_aux);

	// esecuzione query
	const char* parameters[4] = {v_aux[0].c_str(), v_aux[1].c_str(), v_aux[2].c_str(), v_aux[3].c_str() };
	PGresult* stmt = PQprepare(conn, "creazione_ordine", "INSERT INTO ordine (lista, indirizzo, provider, status) VALUES ($1::integer, $2::integer, $3::varchar, $4::varchar)", 4, NULL);
	res = PQexecPrepared(conn, "creazione_ordine", 4, parameters, NULL, NULL, 0);

	// controllo query
	checkUpdateResults(res, conn);
}

int main() {

	// SETUP INTERFACCIA GRAFICA
	int operazione = 0;
	std::map<unsigned int, std::string> operazioni;

	operazioni[0] = "esci";
	operazioni[1] = "inserimento_utente";
	operazioni[2] = "inserimento_carta_di_credito";
	operazioni[3] = "inserimento_indirizzo";
	operazioni[4] = "eliminazione carrello";
	operazioni[5] = "inserimento_contenuto";
	operazioni[6] = "modifica_quantita_prodotto";
	operazioni[7] = "creazione_ordine";

	// SETUP CONNESSIONE al DB
	PGconn* conn;
	char conninfo [250];
	sprintf(conninfo, "user=%s password=%s dbname=%s hostaddr=%s port=%d" ,
			PG_USER , PG_PASS , PG_DB , PG_HOST , PG_PORT ) ;
	
	// APERTURA DELLA CONNESSIONE
	conn = PQconnectdb(conninfo);

	// CONTROLLO DELLA CONNESSIONE
	checkConnection(conn);



	do {
		std::cout << "INTERFACCIA DB" << std::endl;
		std::cout << "immettere una delle seguenti operazioni" << std::endl;

		for(std::map<unsigned int, std::string>::const_iterator cit = operazioni.begin();
				cit != operazioni.end();
				cit++) {
			std::cout << cit->first << " " << cit->second << std::endl;
		}

		std::cin >> operazione;
		if (operazione == 1) {
			inserimento_utente(conn); 
		} else if (operazione == 2) {
			inserimento_carta_di_credito(conn);
		} else if (operazione == 3) {
			inserimento_indirizzo(conn);
		} else if (operazione == 4) {
			std::cout << "eliminazione spostata" << std::endl;
		} else if (operazione == 5) {
			inserimento_contenuto(conn);
		} else if (operazione == 6) {
			modifica_quantita_prodotto(conn);
		} else if (operazione == 7) {
			std::map<unsigned int, std::string> menu_creazione;
			menu_creazione[0] = "creazione carrello";
			menu_creazione[1] = "aggiungi al carrello";
			menu_creazione[2] = "procedi all'ordine";
			menu_creazione[3] = "elimina carrello";
			menu_creazione[4] = "termina";
			int operazione = 0;
			int id_carrello = 0;
			do {
				std::cout << "CREAZIONE CARRELLO" << std::endl;
				for(auto cit = menu_creazione.begin(); cit != menu_creazione.end(); cit++) {
					std::cout << cit->first << " " << cit->second << std::endl;
				}			
				std::cin >> operazione;
				if (operazione == 0) {
					creazione_carrello(conn);
				} else if (operazione == 1) {
					inserimento_contenuto(conn);
				} else if (operazione == 2) {
					creazione_ordine(conn);
				} else if (operazione == 3) {
					eliminazione_carrello(conn);						
				}
			} while (operazione != 4);
		}
	} while(operazione != 0);
}






























