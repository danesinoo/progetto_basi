#include <cstdio>
#include <iostream>
#include <fstream>
#include "dependencies/libpq-fe.h"


#define PG_HOST "127.0.0.1" // oppure " localhost " o " postgresql "
#define PG_USER "postgres" // nome utente
#define PG_DB "EClothMountainDb" // nome database
#define PG_PASS "password" // nome password
#define PG_PORT 5432 // numero della porta

void checkResults(PGresult* res, const PGconn* conn) {

	// PGRES_TUPLES_OK,			/* a query command that returns tuples was
	// PGRES_COMMAND_OK
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::cout << "Qualcosa è andato storto." << std::endl;
		PQclear(res);
		exit(1);
	}
}

void printResults(PGresult* res) {
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

int main() {
	PGconn* conn;
  char conninfo [250];
	sprintf(conninfo, "user=%s password=%s dbname=%s hostaddr=%s port=%d" ,
PG_USER , PG_PASS , PG_DB , PG_HOST , PG_PORT ) ;
	conn = PQconnectdb(conninfo);
	
	if(PQstatus(conn) != CONNECTION_OK) {
		std::cout << "Errore di connessione " << PQerrorMessage(conn) << std::endl;
		
		
	} else {
		std::cout << "connessione avvenuta correttamente" << std::endl;

		// oggetto che detiene il risultato di una query.
		PGresult* res;

		// esecuzione di una query normale
		 res = PQexec(conn, "SELECT * FROM utente");

		// esecuzione di una query parametrica

		/*
		PGresult* stmt = PQprepare(conn, "inserimento_utente", "INSERT INTO utente (email, password, nome, cognome) VALUES ($1::varchar, $2::varchar, $3::varchar, $4::varchar)", 4, NULL);


		std::string email = "matilde.basso02@gmail.com";
		std::string password = "asdflkajsdf";
		std::string nome = "leonardo";
		std::string cognome = "basso";

		const char* parameters[4] = {email.c_str(), password.c_str(), nome.c_str(), cognome.c_str()};
		// const char* parameter[2] = {nome.c_str(), email.c_str()};

		res = PQexecPrepared(conn, "selezione_utente", 4, parameters, NULL, NULL, 0);
		*/
		// esecuzione della query
		// controllo che tutto sia andato bene
		checkResults(res, conn);

		// stampa dei risultati
		printResults(res);
	}

	PQfinish(conn);
	exit(1);

	
	return 0;
}
