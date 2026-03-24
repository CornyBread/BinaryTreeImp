#include "database.hpp"

#include <stdexcept>
#include <utility>

Database::Database(const std::string& connection_string)
    : connection_(connection_string) {
    if (!connection_.is_open()) {
        throw std::runtime_error("No se pudo abrir la conexion a PostgreSQL.");
    }
}

bool Database::is_connected() const noexcept {
    return connection_.is_open();
}

pqxx::result Database::query(const std::string& sql) {
    pqxx::work tx{connection_};
    auto result = tx.exec(sql);
    tx.commit();
    return result;
}

std::size_t Database::execute(const std::string& sql) {
    pqxx::work tx{connection_};
    auto affected_rows = tx.exec(sql).affected_rows();
    tx.commit();
    return affected_rows;
}

std::string Database::quote(const std::string& value) const {
    return connection_.quote(value);
}
