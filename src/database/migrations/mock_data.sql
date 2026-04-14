-- Ejecutar despues de italy_mafia.sql.
\connect italy_mafia;

BEGIN;

TRUNCATE TABLE members RESTART IDENTITY CASCADE;

INSERT INTO members (id, name, last_name, gender, age, id_boss, is_dead, in_jail, was_boss, is_boss)
VALUES
	(1,  'Vito',     'Corleone', 'H', 68, NULL, 0, 0, 1, 1),
	(2,  'Sonny',    'Corleone', 'H', 40, 1,    1, 0, 0, 0),
	(3,  'Michael',  'Corleone', 'H', 35, 1,    0, 0, 0, 0),
	(4,  'Fredo',    'Corleone', 'H', 32, 2,    0, 0, 0, 0),
	(5,  'Connie',   'Corleone', 'M', 30, 2,    0, 0, 0, 0),
	(6,  'Tom',      'Hagen',    'H', 45, 3,    0, 1, 0, 0),
	(7,  'Kay',      'Adams',    'M', 33, 3,    0, 0, 0, 0),
	(8,  'Vincent',  'Mancini',  'H', 22, 4,    0, 0, 0, 0),
	(9,  'Mary',     'Corleone', 'M', 21, 4,    0, 0, 0, 0),
	(10, 'Anthony',  'Corleone', 'H', 18, 5,    0, 0, 0, 0),
	(11, 'Santino',  'Corleone', 'H', 16, 5,    0, 0, 0, 0),
	(12, 'Lucia',    'Romano',   'M', 28, 6,    0, 0, 0, 0),
	(13, 'Marco',    'Bellini',  'H', 29, 6,    0, 0, 0, 0),
	(14, 'Elena',    'Greco',    'M', 26, 7,    0, 0, 0, 0),
	(15, 'Paolo',    'Greco',    'H', 24, 7,    0, 0, 0, 0);

COMMIT;
