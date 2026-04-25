height = 0

while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Enter a valid height")

for i in range(height):
    # This prints only: Spaces + Left Hashes
    print(" " * (height - 1 - i) + "#" * (i + 1))
