# Write a program that imports data from a CSV spreadsheet
#
# Your program should accept the name of a CSV file as a CLI argument
# - Incorrect number of CLI arguments = print an error and exit
# - You may assume that the CSV File will exist,
#   and will have columns "name", "house" and "birth"
#
# For each student, insert the student into the students table in the "students.db"
# Parse each name, so that we get "first", "middle" and "last" name.
# Not all students have a middle name! "middle" = "NULL"
# Check for two space-separated names (first, and last name) or
# Check for three space-separated names (first, middle and last name)
#
# Usage example:"python import.py characters.csv"

from cs50 import SQL
import sys
import csv


def main():
    # Check CLI arguments
    if len(sys.argv) != 2:
        print("Incorrect number of command-line arguments")
        print("Usage: python import.py characters.csv")
        sys.exit(1)

    # Check if we got a csv file
    filename = sys.argv[1]
    if not filename.endswith(".csv"):
        print("The given file is not a csv file!")
        sys.exit(1)

    # Give access to database
    db = SQL("sqlite:///students.db")

    # create a DictReader
    file = open(sys.argv[1])
    fileReader = csv.DictReader(file)

    # Create list an fill it from the dict, so that we can query it
    for line in fileReader:
        name = (line['name'].split())
        house = (line['house'])
        birth = (line['birth'])

        # insert 'none' for middle name, for students witout a middle name
        if (len(name) == 2):
            name.insert(1, None)

        # Put everything together
        name.append(house)
        name.append(birth)

        # Insert the list into the "students.db"
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[:5])


if __name__ == "__main__":
    main()