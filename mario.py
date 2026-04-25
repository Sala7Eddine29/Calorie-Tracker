# Initialize height to an invalid value to start the loop
height = 0

# Prompt user for height between 1 and 8 inclusive
while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        # Handle cases where the user does not enter an integer
        print("Enter a valid height")

# Iterate through each row of the pyramid
for i in range(height):
    # Print leading spaces for the left pyramid
    print(" " * (height - 1 - i), end="")

    # Print the left side hashes
    print("#" * (i + 1), end="")

    # Print the gap (two spaces)
    print("  ", end="")

    # Print the right side hashes
    print("#" * (i + 1))
