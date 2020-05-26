# Import cs50, csv, sys libary
import cs50
import csv
import sys
from itertools import groupby

# TODO:
# - Open DNA sequence, read contents into memory >> DONE
# - Open CSV file, read contents into memmory >> DONE
# - For each STR (Short Tandem Repeats), compute the longest run of consectuive repeats in the DNA sequence
# - Compare the STR counts against each row in the CSV file,


def main():
    # Check the number of command-line arguments, if more or less than two are given, exit the program
    if len(sys.argv) != 3:
        print("Incorrect number of command-line arguments")
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)


    # Read DNA sequence, load into a string and close the file
    dnaFile = open(sys.argv[2])
    dnaString = dnaFile.read()
    dnaFile.close()
    print(dnaString)    # Debugging


    # Read CSV file, load the STRs from the first Row in the Database
    csvFile = open(sys.argv[1])
    csvReader = csvFile.read()
    print(csvReader)
    for row in csvReader:
        # Read the first row of the Database
        strs = row[1:]
        # Remove the first column of the database, so we only get the "STR"s in a list
        strs.pop(0)
        # We break out of the loop
        break
    print(strs)  # Debugging
    print("Test")

    # count number of occurences of each STR in sequence.txt and store value in dict dna_fingerprint
    dnaSequence = {}
    for str in strs:
        dnaSequence[str] = countRepeats(str, dnaString)
        print(dnaSequence)  # Debugging


# Function that counts consecutive repeats of a STR in a given DNA Sequence
def countRepeats(str, dnaString):
    i = 0
    while str*(i+1) in dnaString:
        i += 1
    return (i)


if __name__ == "__main__":
    main()