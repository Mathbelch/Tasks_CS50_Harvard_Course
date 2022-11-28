

def main():
    i = 0
    while i == 0:
        # Asking user input for height. If the input is not an int, it will jump to the 'except' block
        try:
            height = int(input("height: "))
            if (height >= 1) and (height <= 8):
                i += 1
        except:
            i = 0

    for j in range(height):
        # Printing the pyramid align to the left.
        print(" " * (height - (j + 1)) + "#" * (j + 1) + "  " + "#" * (j + 1))


main()
