#include "database/database.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int main() {
	
	const char* env_connection = std::getenv("DATABASE_URL");
	std::string connection_string =
		env_connection != nullptr
			? std::string{env_connection}
			: "host=localhost port=5432 dbname=italy_mafia user=postgres password=448699*";

	
	return 0;
}
