def main():
    numberLetters = 0
    numberWords = 0
    numberSentences = 0
    letterPerCentWords = 0
    sentencesPerCentWords = 0
    clIndex = -1

    text = str(input("Text: "))
    sizeText = len(text)

    for c in text:
        if (c.isalpha()):
            numberLetters += 1
        elif (c.isspace()):
            numberWords += 1
        elif (c == "." or c == "!" or c == "?"):
            numberSentences += 1

    # Here we need to make a correction in the 'number_words' parameter. We can't declare it as 1 in case of no words typed.
    if (numberWords > 0):
        numberWords += 1

    # Now let's calculate the Coleman-Liau Index.
    letterPerCentWords = ((numberLetters * 100) / numberWords)
    sentencesPerCentWords = ((numberSentences * 100) / numberWords)
    clIndex = round(((0.0588 * letterPerCentWords) - (0.296 * sentencesPerCentWords) - 15.8))

    # Finally, let's give the result:
    if (clIndex == -1):
        print("ERROR\n")
    elif (clIndex <= 1):
        print("Before Grade 1\n")
    elif (clIndex >= 16):
        print("Grade 16+\n")
    else:
        print(f"Grade {clIndex}")


main()