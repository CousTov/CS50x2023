import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

students = []
houses = []
with open("students.csv", "r") as csvFile:
    reader = csv.DictReader(csvFile)
    for row in reader:
        count = 0
        stdName = row["student_name"]
        stdID = row["id"]
        house = row["house"]
        head = row["head"]
        if stdName not in students:
            students.append({"std": stdName})
        for h in houses:
            if h["house"] == house:
                count += 1
        if count == 0:
            houses.append({"house": house, "head": head})


for student in students:
    db.execute("INSERT INTO studentNames (stdName) VALUES (?)", students["std"])

for house in houses:
    db.execute("INSERT INTO houseNames (house, head) VALUES (?, ?)", houses["house"], house["head"])
