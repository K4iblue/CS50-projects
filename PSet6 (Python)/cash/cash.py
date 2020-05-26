# Import get_float from the cs50 libary
from cs50 import get_float

# US coins
quarter = 25
dime = 10
nickel = 5
penny = 1

coins = 0
change = 0.00

# Ask user, how much change is owed
while change <= 0:
    change = get_float("Change owed: ")

# Round change so we get an int
ch_round = round(change * 100)

# Check how many "quarters" we can use
while ch_round >= quarter:
    ch_round -= quarter
    coins += 1

# Check how many "dimes" we can use
while ch_round >= dime:
    ch_round -= dime
    coins += 1

# Check how many "nickels" we can use
while ch_round >= nickel:
    ch_round -= nickel
    coins += 1

# Check how many "pennys" we can use
while ch_round >= penny:
    ch_round -= penny
    coins += 1

print(coins)