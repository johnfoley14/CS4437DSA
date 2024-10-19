import csv
import os
import time


os.chdir("/home/djk/Development/ise/srp-cs4437/DSA/cpp/git/CS4437DSA/PythonTests/no_directory")

pathList = []
pathToCsvs = "/home/djk/Development/ise/srp-cs4437/DSA/cpp/git/CS4437DSA/PythonTests/no_directory/csvs/"

def read_csvs(file_paths):
    start_time = time.time()

    for i, path in enumerate(file_paths):
        with open(path, mode="r") as file:
            reader = csv.reader(file)
            for _row in reader:
                print(f"Reading File: {i} / {len(file_paths)}", end='\r', flush=True)
    end_time = time.time()
    return end_time - start_time


with open('../words.csv', mode="r") as file:
    reader = csv.reader(file)
    next(reader)
    pathList = [pathToCsvs + word[0] + ".csv" for word in reader]

timeToRead = read_csvs(pathList)
print(f"Average time to read {len(pathList)} csvs was: {timeToRead/len(pathList)*1_000}ms")

