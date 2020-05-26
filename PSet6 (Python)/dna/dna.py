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

    # Open CSV file, and create a reader variable
    csvFile = open(sys.argv[1])
    dbReader = csv.DictReader(csvFile)
    strs = dbReader.fieldnames[1:]

    # count number of occurences of each STR in sequence.txt and store value in dict dna_fingerprint
    dnaSequence = {}
    for str in strs:
        dnaSequence[str] = countRepeats(str, dnaString)


# Now we search throught the CSV file to find a matching name
    for row in dbReader:
        # If a match is found, print the corresponding name, close all files and end the program
        if match(strs, dnaSequence, row):
            print(f"{row['name']}")
            csvFile.close()
            return

    # If we found no matching name
    print("No match")
    csvFile.close()


# Function that counts consecutive repeats of a STR in a given DNA Sequence
def countRepeats(str, dnaString):
    i = 0
    while str*(i+1) in dnaString:
        i += 1
    return (i)


# Function that determines if a STRs matches a row from the CSV File
def match(strs, dnaSequence, row):
    for str in strs:
        if dnaSequence[str] != int(row[str]):
            return False
    return True


if __name__ == "__main__":
    main()