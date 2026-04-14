-- Ejecutar este script con un superusuario o un usuario con permisos para crear bases.

CREATE DATABASE italy_mafia;

\connect italy_mafia;

CREATE TABLE IF NOT EXISTS members (
	id INTEGER PRIMARY KEY,
	name VARCHAR(60) NOT NULL,
	last_name VARCHAR(60) NOT NULL,
	gender CHAR(1) NOT NULL CHECK (gender IN ('H', 'M')),
	age SMALLINT NOT NULL,
	id_boss INTEGER NULL,
	is_dead SMALLINT NOT NULL DEFAULT 0 CHECK (is_dead IN (0, 1)),
	in_jail SMALLINT NOT NULL DEFAULT 0 CHECK (in_jail IN (0, 1)),
	was_boss SMALLINT NOT NULL DEFAULT 0 CHECK (was_boss IN (0, 1)),
	is_boss SMALLINT NOT NULL DEFAULT 0 CHECK (is_boss IN (0, 1))
);
