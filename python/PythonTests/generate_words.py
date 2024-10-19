import csv
import nltk
from nltk.corpus import brown
from nltk.probability import FreqDist
import os

os.chdir("/home/djk/Development/ise/srp-cs4437/DSA/cpp/git/CS4437DSA/PythonTests")

nltk.download('brown')
words = brown.words()

# Create a frequency distribution of the words
freq_dist = FreqDist(word.lower() for word in words if word.isalpha())  # Keep only alphabetic words

most_common_words = [word for word, _freq in freq_dist.most_common(10_000)]

with open('words.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Word'])
    for word in most_common_words:
        writer.writerow([word])

print("CSV file 'words.csv' created successfully.")
