import csv
import os
import random

os.chdir("/home/djk/Development/ise/srp-cs4437/DSA/cpp/git/CS4437DSA/PythonTests/no_directory")

if not os.path.exists("./csvs"):
    os.mkdir("csvs")

def random_row(i):
    return [i, random.randint(1,1000), random.randint(1,1000)]

with open('../words.csv', mode="r", newline="") as file:
    reader = csv.reader(file, delimiter=" ")
    next(reader)
    for word in reader:
        with open("./csvs/" + word[0] + ".csv", mode="w", newline="") as wordFile:
            writer = csv.writer(wordFile)
            writer.writerow(["BookIndex", "Frequency", "TotalCount"])

            writer.writerows(random_row(i) for i in range(500))

print("CSVs created successfully")
