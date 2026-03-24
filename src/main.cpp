#include "database.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int main() {
	
// 	const char* env_connection = std::getenv("DATABASE_URL");
// 	std::string connection_string =
// 		env_connection != nullptr
// 			? std::string{env_connection}
// 			: "host=localhost port=5432 dbname=postgres user=postgres password=postgres";

// 	try {
// 		Database db{connection_string};
// 		if (!db.is_connected()) {
// 			std::cerr << "No se pudo establecer la conexion con PostgreSQL.\n";
// 			return 1;
// 		}

// 		const auto now_result = db.query("SELECT NOW() AS server_time;");
// 		if (!now_result.empty()) {
// 			std::cout << "Server time: " << now_result[0]["server_time"].c_str() << '\n';
// 		}

// 		const std::string member_name = "Vito";
// 		const auto name_result = db.query(
// 			"SELECT id, name, last_name FROM members WHERE name = " + db.quote(member_name) +
// 			" LIMIT 5;");

// 		std::cout << "Miembros encontrados: " << name_result.size() << '\n';
// 	} catch (const std::exception& ex) {
// 		std::cerr << "Error: " << ex.what() << '\n';
// 		return 1;
// 	}

// 	return 0;
}
