-- Daniel Nick CMSC 362 Lab 3

DROP TABLE IF EXISTS rants;
DROP TABLE IF EXISTS accounts;
DROP TABLE IF EXISTS comments;
DROP TABLE IF EXISTS ratings;
CREATE TABLE rants ( username     TEXT,
    		     rant         TEXT,
		     post_id      SERIAL PRIMARY KEY,
		     time_posted  TIMESTAMP);

CREATE TABLE accounts ( username    TEXT PRIMARY KEY,
    			password    TEXT  NOT NULL,
			image       BYTEA);

CREATE TABLE comments ( username      TEXT,
    			post_id       SERIAL,
			comment_id    INTEGER,
			comment_text  TEXT,
			PRIMARY KEY(post_id, comment_id));

CREATE TABLE ratings (  post_id	      SERIAL,
    			username      TEXT,
			rating	      INTEGER DEFAULT 5 CONSTRAINT rating_range CHECK(rating >= 1 AND rating <= 10),
			PRIMARY KEY(post_id, username));


INSERT INTO accounts (username, password) VALUES ('frank', md5('dumbPassword'));

INSERT INTO accounts (username, password) VALUES ('tom', md5('fish1'));

INSERT INTO accounts (username, password) VALUES ('harry', md5('fish2'));

INSERT INTO accounts (username, password) VALUES ('celeste', md5('fish3'));


INSERT INTO rants (username, rant, post_id) VALUES ('Sparkelz', 'Saw a beautiful rainbow today!', 1);

INSERT INTO rants (username, rant, post_id, time_posted) VALUES ('Apocolypse1', 'Because Apocolypse was taken.', 2, '2017-02-13');

INSERT INTO rants (username, rant, post_id) VALUES ('FemiNazi', 'WE MUST BREAK THROUGH THE GLASS CEILING!', 3);

INSERT INTO rants (username, rant, post_id) VALUES ('NewsReporter', 'As of late, there has been mass death in aquariums around the US with the shattering of glass ceilings.', 4);

INSERT INTO rants (username, rant, post_id) VALUES ('EliteGamer',' When does Zelda defeat Ganondorf and save the princess?', 5);

INSERT INTO comments (username, post_id, comment_id, comment_text) VALUES ('AquariumDirector', 3, 1, 'PLEASE STOP SHATTERING THE GLASS CEILINGS!');

INSERT INTO comments (username, post_id, comment_id, comment_text) VALUES ('FemiNazi', 2, 2, 'DOWN WITH THE PATRIARCHY!');

INSERT INTO ratings (post_id, username, rating) VALUES (1, 'Mean_dude', 1);
INSERT INTO ratings (post_id, username, rating) VALUES (1, 'Superman', 4);
INSERT INTO ratings (post_id, username, rating) VALUES (3, 'Sympathy', 9);
INSERT INTO ratings (post_id, username, rating) VALUES (5, 'John_doe', 5);
INSERT INTO ratings (post_id, username, rating) VALUES (5, 'Doe_Doe', 6);
INSERT INTO ratings (post_id, username, rating) VALUES (5, 'Link', 10);
INSERT INTO ratings (post_id, username, rating) VALUES (3, 'Glass_Blower', 2);

SELECT * FROM rants;

SELECT * FROM comments;

SELECT COUNT(username) FROM accounts;
SELECT SUM(rating)/COUNT(rating) AS Average FROM ratings GROUP BY post_id;
SELECT (SUM(rating) - MAX(rating) - MIN(rating))/(COUNT(rating) - 2) AS Average2 FROM ratings;
SELECT username AS name, rant, time_posted, COUNT(post_id) FROM rants NATURAL JOIN (SELECT post_id FROM comments) AS comment  GROUP BY post_id;
SELECT username, rant FROM rants ORDER BY username;
