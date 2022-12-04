import csv
import sys


def main():
    # First we must check the command line arguments.
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequency.txt")
        sys.exit(1)
    else:
        # If it's all good, we can open the DNA sequence txt file:
        seqName = sys.argv[2]
        with open(seqName, "r") as seqDNA:
            sequenceDNA = seqDNA.readline()
        seqDNA.close()
        # And also the DNA database file:
        databaseName = sys.argv[1]
        with open(databaseName, "r") as database:
            databaseCSV = csv.reader(database, delimiter=",")
            sequencesSTR = []
            sequencesSTR = next(databaseCSV)  # getting the header to a list
            sequencesSTR.pop(0)  # Removing the 'name' from the list.
            rows = []
            for row in databaseCSV:
                rows.append(row)  # Getting list with the names and number of sequences of STRs for people on database

        # Now we can count the longest run of consecutive repeats for each STR in the DNA sequence and keep it on the  list.
        counter = []
        for i in range(len(sequencesSTR)):
            counter.append(countSequence(sequencesSTR[i], sequenceDNA))

        # Now we can iterate the csv database to check who is the persons with STR counters that match the sample.
        print(findMatch(rows, counter))


def countSequence(sequenceSTR, sequenceDNA):
    longestSTR = 0  # will keep track of the logest repeated number of the STR sequence in the DNA sequence.
    # variables used to check if we found a STR sequence.
    sizeBase = len(sequenceSTR)
    sizeDNA = len(sequenceDNA)

    for baseDNA in range(sizeDNA - 1):
        counterDNA = baseDNA
        matchBase = 0  # store the number of bases in DNA that matches the STR in sequence.
        repeats = 0  # store the number of STR consecutive sequences in DNA sample
        keep = True
        while keep == True:
            for baseSTR in sequenceSTR:
                if counterDNA <= (sizeDNA - 1):
                    if (matchBase == sizeBase):
                        repeats += 1
                        matchBase = 0
                        if (longestSTR < repeats):
                            longestSTR = repeats
                    if (sequenceDNA[counterDNA] == baseSTR):
                        counterDNA += 1
                        matchBase += 1
                    else:
                        keep = False
                        break
                else:
                    keep = False
                    break
    return longestSTR


def findMatch(rows, counter):
    for i in range(len(rows)):  # gets the rows of the csv file, with names and number of repeated STR sequences
        # since the first column is the person's name, let's compare the other columns with the number of repeated STR samples (counter)
        for j in range(1, len(rows[i])):
            if ((int(rows[i][j])) == counter[j - 1]):
                equals = True
            else:
                equals = False
                break
        if (equals == True):
            matchPerson = rows[i][0]
            break
        else:
            continue

    if (equals == False):
        matchPerson = "No match"
    return matchPerson


main()