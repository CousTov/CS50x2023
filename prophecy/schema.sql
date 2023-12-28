CREATE TABLE studentNames(
    id INTEGER,
    stdName TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houseNames(
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE assigns(
    stdID INTEGER,
    houseID INTEGER,
    FOREIGN KEY(stdID) REFERENCES studentNames(id),
    FOREIGN KEY(houseID) REFERENCES houseNames(id)
);