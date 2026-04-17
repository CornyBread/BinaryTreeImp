#include "database/database.hpp"
#include "family_tree.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

Member row_to_member(const pqxx::row& row) {
	Member member{};
	member.id = row["id"].as<int>();
	member.name = row["name"].c_str();
	member.last_name = row["last_name"].c_str();
	member.gender = row["gender"].c_str()[0];
	member.age = row["age"].as<int>();
	member.id_boss = row["id_boss"].is_null() ? -1 : row["id_boss"].as<int>();
	member.is_dead = row["is_dead"].as<int>() != 0;
	member.in_jail = row["in_jail"].as<int>() != 0;
	member.was_boss = row["was_boss"].as<int>() != 0;
	member.is_boss = row["is_boss"].as<int>() != 0;
	return member;
}

}  // namespace

int main() {
	const char* env_connection = std::getenv("DATABASE_URL");
	std::string connection_string =
		env_connection != nullptr
			? std::string{env_connection}
			: "host=localhost port=5432 dbname=italy_mafia user=postgres password=448699*";

	try {
		Database db{connection_string};
		if (!db.is_connected()) {
			std::cerr << "No se pudo establecer la conexion con PostgreSQL.\n";
			return 1;
		}

		const auto rows = db.query(
			"SELECT id, name, last_name, gender, age, id_boss, is_dead, in_jail, was_boss, is_boss "
			"FROM members ORDER BY id;");

		FamilyTree tree;
		std::size_t inserted_count = 0;

		while (inserted_count < rows.size()) {
			bool progress = false;

			for (const auto& row : rows) {
				const Member member = row_to_member(row);
				if (tree.insert(member)) {
					++inserted_count;
					progress = true;
				}
			}

			if (!progress) {
				break;
			}
		}

		std::cout << "Miembros cargados en el arbol: " << inserted_count << " de " << rows.size() << "\n";
		std::cout << "\nArbol completo (preorden):\n";
		tree.printAll();

		std::cout << "\nLinea de sucesion viva (preorden):\n";
		tree.printLiving();

		Member boss_before{};
		if (tree.getCurrentBoss(boss_before)) {
			std::cout << "\nBoss actual: " << boss_before << "\n";
		} else {
			std::cout << "\nBoss actual: no definido\n";
		}

		if (tree.applyBossRules()) {
			Member boss_after{};
			if (tree.getCurrentBoss(boss_after)) {
				std::cout << "Boss despues de aplicar reglas: " << boss_after << "\n";
			}
		} else {
			std::cout << "No se pudo asignar un boss valido con las reglas actuales.\n";
		}

		if (inserted_count != rows.size()) {
			std::cout << "\nAviso: hubo registros que no se pudieron insertar. Revisa id_boss y duplicados.\n";
		}
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
		return 1;
	}

	return 0;
}
