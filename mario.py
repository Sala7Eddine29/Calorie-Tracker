height = 0

while height < 1 or height > 8:
    try:
        height = int(input("height: "))
    except ValueError:
        print("enter a valid height")

for i in range(height):
    # This prints: Spaces + Left Hashes + Middle Gap + Right Hashes
    print(" " * (height - 1 - i) + "#" * (i + 1) + "  " + "#" * (i + 1))
