CREATE TABLE Users(
	idUser INT(4) AUTO_INCREMENT NOT NULL PRIMARY KEY,
	username  VARCHAR(30) NOT NULL,
	fName VARCHAR(30) NOT NULL,
	lName VARCHAR(30) NOT NULL,
	pass VARCHAR(30) NOT NULL
);

CREATE TABLE House(
	idHouse INT(4) AUTO_INCREMENT NOT NULL PRIMARY KEY,
	houseName  VARCHAR(30) NOT NULL,
	address  VARCHAR(30) NOT NULL,
	num INT(4) NOT NULL,
	phone VARCHAR(10) NOT NULL,
	username VARCHAR(30) NOT NULL
);
CREATE TABLE Actuator(
	idActuator INT(4) AUTO_INCREMENT NOT NULL PRIMARY KEY,
	name  VARCHAR(30) NOT NULL,
	status INT(1) NOT NULL,
	houseName VARCHAR(30) NOT NULL,
	username VARCHAR(30) NOT NULL
);
CREATE TABLE Sensor(
	idSensor INT(4) AUTO_INCREMENT NOT NULL PRIMARY KEY,
	name  VARCHAR(30) NOT NULL,
	houseName VARCHAR(30) NOT NULL,
	username VARCHAR(30) NOT NULL,
	readVal INT(5) NOT NULL
);

INSERT INTO Sensor (name,houseName,username,readVal) VALUES("TempSensor","myHouse","myUser",20);
INSERT INTO Actuator (name,status,houseName,username) VALUES("Foco 1",0,"myHouse","myUser");
INSERT INTO Actuator (name,status,houseName,username) VALUES("Foco 2",0,"myHouse","myUser");
INSERT INTO Actuator (name,status,houseName,username) VALUES("Foco 3",0,"myHouse","myUser");
