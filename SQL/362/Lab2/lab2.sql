-- Daniel Nick CMSC 362 Lab 2

DROP TABLE IF EXISTS rants;
DROP TABLE IF EXISTS accounts;
DROP TABLE IF EXISTS comments;

CREATE TABLE rants ( username     TEXT,
    		     rant         TEXT,
		     post_id      SERIAL,
		     time_posted  TIMESTAMP);

CREATE TABLE accounts ( username    TEXT,
    			password    TEXT  NOT NULL,
			iamge       BYTEA);

CREATE TABLE comments ( username      TEXT,
    			post_id       INTEGER,
			comment_id    SERIAL,
			comment_text  TEXT);

INSERT INTO accounts (username, password) VALUES ('Sparkelz', md5('dumbPassword'));

INSERT INTO accounts (username, password) VALUES ('Apocolypse1', md5('fish1'));

INSERT INTO accounts (username, password) VALUES ('FemiNazi', md5('fish2'));

INSERT INTO accounts (username, password) VALUES ('NewsReporter', md5('fish3'));

INSERT INTO accounts (username, password) VALUES ('EliteGamer', md5('PCmasterRace'));


INSERT INTO rants (username, rant, post_id) VALUES ('Sparkelz', 'Saw a beautiful rainbow today!', 1);

INSERT INTO rants (username, rant, post_id, time_posted) VALUES ('Apocolypse1', 'Because Apocolypse was taken.', 2, '2017-02-13');

INSERT INTO rants (username, rant, post_id) VALUES ('FemiNazi', 'WE MUST BREAK THROUGH THE GLASS CEILING!', 3);

INSERT INTO rants (username, rant, post_id) VALUES ('NewsReporter', 'As of late, there has been mass death in aquariums around the US with the shattering of glass ceilings.', 4);

INSERT INTO rants (username, rant, post_id) VALUES ('EliteGamer',' When does Zelda defeat Ganondorf and save the princess?', 5);

INSERT INTO comments (username, post_id, comment_id, comment_text) VALUES ('AquariumDirector', 3, 1, 'PLEASE STOP SHATTERING THE GLASS CEILINGS!');

INSERT INTO comments (username, post_id, comment_id, comment_text) VALUES ('FemiNazi', 3, 2, 'DOWN WITH THE PATRIARCHY!');

SELECT * FROM rants;

SELECT * FROM comments;

SELECT * FROM accounts;
