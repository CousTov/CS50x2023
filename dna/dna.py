import csv
import sys


def main():

    # TODO: Check for command-line usage -- DONE
    if len(sys.argv) != 3:
        print("Usage: python dna.py DATABASE.CSV DNASEQUENCE.TXT")
        sys.exit(1)

    # TODO: Read database file into a variable -- DONE
    dnaDatabase = []
    with open(sys.argv[1]) as database:
        reader = csv.reader(database)
        for row in reader:
            dnaDatabase.append(row)

    # TODO: Read DNA sequence file into a variable -- DONE
    with open(sys.argv[2]) as dna:
        dnaSeq = dna.read()

    # TODO: Find longest match of each STR in DNA sequence -- DONE
    # To store the STR subsequences
    strList = []
    # To store the keys (STR subsequence) and values (longest occurance)
    strDict = {}
    # Storing STRs as lists
    for i in range(1, len(dnaDatabase[0])):
        strList.append(dnaDatabase[0][i])
    # Storing STRs and their longest occurance
    for i in range(len(strList)):
        strDict = {**strDict, strList[i]: longest_match(dnaSeq, strList[i])}

    # TODO: Check database for matching profiles -- DONE
    # Default value to return
    default = "No match"
    # Count to keep track of the matching STR data
    count = 0
    # Looping through data list inside the Database list
    for i in range(1, len(dnaDatabase)):
        # loopinjg through the STR list
        for j in range(len(strList)):
            # Comparing if the longest STR chain value matches to person's respective STR values in database
            if strDict[strList[j]] == int(dnaDatabase[i][j+1]):
                # if it does, increase count
                count += 1
        # After first data list in database is compared, checking if count equals list of STRs
        if count == len(strList):
            # if it does, print the name and exit
            print(dnaDatabase[i][0])
            sys.exit(0)
        # if it does not, reset count to 0
        else:
            count = 0
    # if nothing is fount, print default value and exit
    print(default)
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
