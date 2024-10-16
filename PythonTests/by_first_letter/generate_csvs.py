import csv
import os
import random
import string

os.chdir("/home/djk/Development/ise/srp-cs4437/DSA/cpp/git/CS4437DSA/PythonTests/by_first_letter")

if not os.path.exists("./csvs"):
    os.mkdir("csvs")

for letter in string.ascii_lowercase:
    if not os.path.exists(f"./csvs/{letter}"):
        os.mkdir(f"./csvs/{letter}")

def random_row(i):
    return [i, random.randint(1,1000), random.randint(1,1000)]

with open('../words.csv', mode="r", newline="") as file:
    reader = csv.reader(file, delimiter=" ")
    next(reader)
    for word in reader:
        with open(f"./csvs/{word[0][0]}/{word[0]}.csv", mode="w", newline="") as wordFile:
            writer = csv.writer(wordFile)
            writer.writerow(["BookIndex", "Frequency", "TotalCount"])

            writer.writerows(random_row(i) for i in range(500))

print("CSVs created successfully")
