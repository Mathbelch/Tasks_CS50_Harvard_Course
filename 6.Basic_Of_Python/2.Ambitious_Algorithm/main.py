def main():
    valueReal = askForChangeValue()
    valueCents = convertToCents(valueReal)
    amountCoins = countCoins(valueCents)
    print(amountCoins)


def askForChangeValue():
    i = 0
    while i == 0:
        # Asking user input for the change value. If the input is not a positive float, it will ask the value again.
        try:
            value = float(input("Insert the change amount you need to give to the client: R$ "))
            if (value >= 0):
                i += 1
                return value
        except:
            i = 0


def convertToCents(valueReal):
    cents = round(valueReal * 100, None)
    return cents


def countCoins(remaining):
    totalAmount = 0
    while (remaining >= 25.0):
        qtd_25 = int(remaining / 25)
        remaining -= (qtd_25 * 25)
        totalAmount += qtd_25
    while (remaining >= 10.0):
        qtd_10 = int(remaining / 10)
        remaining -= (qtd_10 * 10)
        totalAmount += qtd_10
    while (remaining >= 5.0):
        qtd_5 = int(remaining / 5)
        remaining -= (qtd_5 * 5)
        totalAmount += qtd_5
    while (remaining >= 1.0):
        qtd_1 = int(remaining)
        remaining -= qtd_1
        totalAmount += qtd_1
    return totalAmount


main()
