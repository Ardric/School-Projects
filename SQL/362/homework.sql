DROP TABLE IF EXISTS Boats;
DROP TABLE IF EXISTS Owners;

CREATE TABLE Boats(
  	name		TEXT,
	owner_last	TEXT,
	owner_first	TEXT,
	boat_len	INTEGER
    );

CREATE TABLE Owners(
  	last_name	TEXT,
	first_name	TEXT,
	age		INTEGER
    );

INSERT INTO Boats VALUES ('Titan', 'Lowdermilk', 'Daniel', 80);
INSERT INTO Boats VALUES ('PeeWee', 'Lewis', 'Ray', 15);
INSERT INTO Boats VALUES ('AvgJoe', 'Swanson', 'Joe', 40);
INSERT INTO Boats VALUES ('Blitz', 'Surge', 'Captain', 35);

INSERT INTO Owners VALUES ('Lowdermilk', 'Daniel', 22);
INSERT INTO Owners VALUES ('Lewis', 'Ray', 84);
INSERT INTO Owners VALUES ('Swanson', 'Joe', 64);
INSERT INTO Owners VALUES ('Surge', 'Captain', 50);
