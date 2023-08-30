#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "dependencies/libpq-fe.h"

#define PG_HOST "127.0.0.1" // oppure " localhost " o " postgresql "
#define PG_USER "postgres" // nome utente
#define PG_DB "EClothMountainDB" // nome database
#define PG_PASS "password" // nome password
#define PG_PORT 5432 // numero della porta


void print_messages(const std::map<unsigned int, std::string>& msg) {
	for (auto cit = msg.begin(); cit != msg.end(); cit++) {
		std::cout << cit->second << std::endl;
	}
}

void checkConnection(PGconn* conn) {
	if(PQstatus(conn) != CONNECTION_OK) {
		std::cout << "Errore di connessione " << PQerrorMessage(conn) << std::endl;
		PQfinish(conn);
		exit(1);
	} else {
		std::cout << "connessione avvenuta correttamente" << std::endl;
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

void query_1(PGconn* conn) {

	PGresult* res;

	std::vector<std::string> messaggi = {
		"inserici data inizio",
		"inserici data fine"
	};
	std::vector<std::string> args; 
	get_parameters(messaggi, args);

	const char* parameters[2] = {args[0].c_str(), args[1].c_str()};

	std::string query =  "SELECT lista.utente, sum(contenuto.quantita) FROM lista, contenuto WHERE lista.id = contenuto.lista AND lista.data_creazione > $1::date GROUP BY (lista.utente)";
	PGresult* stmt = PQprepare(conn,"query_1", query.c_str() , 2, NULL);
	
	res = PQexecPrepared(conn, "query_1", 2, parameters, NULL, NULL, 0);
	print_results(res);
}

void query_2(PGconn* conn) {

	PGresult* res;
	std::string query = "SELECT utente.email, count(utente.email) FROM utente, lista, ordine WHERE utente.email = lista.utente AND lista.id = ordine.lista GROUP BY (utente.email)";
	res = PQexec(conn, query.c_str());
	print_results(res);
}

void query_3(PGconn* conn) {
	PGresult* res;
	std::string query = "SELECT email, count(email) FROM ((SELECT utente.email, lista.id from utente, lista WHERE utente.email = lista.utente) as tab left outer join ordine on tab.id = ordine.lista) WHERE lista IS NULL GROUP BY email";
		res = PQexec(conn, query.c_str());
	print_results(res);
}

int main() {
	std::map<unsigned int, std::string> messaggi;
	messaggi[0] = "0: esci";
	messaggi[1] = "1: query 1";
	messaggi[2] = "2: query 2";
	messaggi[3] = "3: query 3";

	std::map<unsigned int, void (*)(PGconn*)> queries;
	queries[1] = &query_1;
	queries[2] = &query_2;
	queries[3] = &query_3;
	
	// SETUP CONNESSIONE al DB
	PGconn* conn;
	char conninfo [250];
	sprintf(conninfo, "user=%s password=%s dbname=%s hostaddr=%s port=%d" ,
			PG_USER , PG_PASS , PG_DB , PG_HOST , PG_PORT ) ;
	
	// APERTURA DELLA CONNESSIONE
	conn = PQconnectdb(conninfo);

	// CONTROLLO DELLA CONNESSIONE
	checkConnection(conn);


	unsigned int operazione = 0;
	do {
		print_messages(messaggi);
		std::cin >> operazione;
		if (operazione != 0) {
			queries[operazione](conn);
		}
	} while(operazione != 0);
} 
