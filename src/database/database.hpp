#pragma once

#include <pqxx/pqxx>

#include <cstddef>
#include <string>

class Database {
public:
    explicit Database(const std::string& connection_string);

    bool is_connected() const noexcept;
    pqxx::result query(const std::string& sql);
    std::size_t execute(const std::string& sql);
    std::string quote(const std::string& value) const;

private:
    pqxx::connection connection_;
};
