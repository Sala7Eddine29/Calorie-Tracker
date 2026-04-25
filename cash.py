from cs50 import get_float

# Initialize change variable and prompt the user for a valid positive amount
change = 0
while change <= 0:
    change = get_float("Change: ")

# Initialize coin counter
coins = 0

# Define a function to calculate the amount of a specific coin to disperse
def reducer(value_to_reduce):
    global change
    global coins
    while change >= value_to_reduce:
        # We round to 10 decimal places to avoid floating-point imprecision errors
        change = round(change - value_to_reduce, 10)
        coins += 1

# Calculate for Quarters (0.25)
reducer(0.25)

# Calculate for Dimes (0.10)
reducer(0.10)

# Calculate for Nickels (0.05)
reducer(0.05)

# Calculate for Pennies (0.01)
reducer(0.01)

# Output the minimum number of coins needed
print(coins)
