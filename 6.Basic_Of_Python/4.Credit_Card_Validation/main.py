def main():
    stringNumber = str(input("Number: "))
    size = len(stringNumber)
    if (luhnAlgorithm(stringNumber)):
        searchFlag(stringNumber[0], stringNumber[1], size)
    else:
        print("INVALID\n")


def luhnAlgorithm(stringNumber):
    cardNumber = []
    cardNumber = stringNumber
    # sum1 will record the sum of the digits multiplied by two (starting from the one in the penultimate position, always jumping one position);
    sum1 = 0
    counter = len(cardNumber) - 2
    while (counter >= 0):
        aux = str(int(cardNumber[counter]) * 2)
        if (int(aux) < 10):
            sum1 += int(aux)
        else:
            auxList = []
            auxList = aux
            sum1 += int(aux[0]) + int(aux[1])
        counter -= 2

    # sum2 will record the sum of the digits that are not multiplied by two (starting from the one in the last position, always jumping one position).
    counter2 = len(cardNumber) - 1
    sum2 = 0
    while (counter2 >= 0):
        sum2 += int(cardNumber[counter2])
        counter2 -= 2

    # sumFinal will record the final sum of Luhn's Algorithm
    sum = sum1 + sum2

    # If the last digit of the sum is zero, the card is valid!
    if (sum % 10 == 0):
        return True
    else:
        return False


def searchFlag(first, second, size):
    if (first == "3" and (second == "4" or second == "7") and size == 15):
        print("AMEX\n")
    elif (first == "5" and (second > "0" and second < "6") and size == 16):
        print("MASTERCARD\n")
    elif (first == "4" and (size == 16 or size == 13)):
        print("VISA\n")
    else:
        print("INVALID\n")


main()