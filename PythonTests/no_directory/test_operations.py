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


averageTimes = []
for i in range(10):
    timeToRead = read_csvs(pathList)
    averageTimes.append(timeToRead/len(pathList) * 1000)
    print(f"[Iteration {i}] Average time to read {len(pathList)} csvs was: {averageTimes[-1]}ms")

averageOfAverages = sum(averageTimes) / 10
print(f"Total Average: {averageOfAverages}ms")
