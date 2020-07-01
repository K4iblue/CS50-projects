# Write a program that prints a list of students for a given house in alphabetical order
#
# Your program should accept the name of a house as a CLI argument
# - Incorrect number of CLI arguments = print an error and exit
#
# Your program should query the "students" table in the "students.db"
# for all of the students in the specific houses
#
# Your program should then print out each students full name and birth year
# formated as example: "Harry James Potter, born 1980"
# - Each student should be printed on their own line
# - Each student should be orderd by last name, for students with the same last name,
#   they should be ordered by first name
#
# Usage example: "python roster.py Gryffindor"

from cs50 import SQL
import sys


def main():
    # Check CLI arguments
    if len(sys.argv) != 2:
        print("Incorrect number of command-line arguments")
        print("Usage: python roster.py 'House Name'")
        sys.exit(1)

    house = sys.argv[1]

    # Give access to database
    db = SQL("sqlite:///students.db")

    # Get all students from the given House, sorted by their last name
    students = db.execute("SELECT * FROM Students WHERE house=? ORDER BY last", (house))

    # Print all student names
    for entries in students:
        if (entries['middle'] == None):
            print(f"{entries['first']} {entries['last']}, born {entries['birth']}")
        else:
            print(f"{entries['first']} {entries['middle']} {entries['last']}, born {entries['birth']}")


if __name__ == "__main__":
    main()