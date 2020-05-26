# Import get_int from the cs50 libary
from cs50 import get_int

# Get user input for the pyramid size
while True:
    height = get_int("Height:")

    # Check if input is valid
    if height >= 1 and height <= 8:
        break

# Print pyramid
for i in range(height):

    # Printing spaces
    for j in range(height - i - 1):
        print(" ", end="")

    # Printing hashes on the left side
    for k in range(- 1, i):
        print("#", end="")

    # Print gap
    print("  ", end="")

    # Printing hashes on the right side
    for j in range(- 1, i):
        print("#", end="")

    # Print new line
    print()