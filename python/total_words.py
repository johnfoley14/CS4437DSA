import csv

with open("../index/BookMetadata.csv") as file:
    reader = csv.reader(file)

    total = 0
    for row in reader:
        total += int(row[2])
print(total)