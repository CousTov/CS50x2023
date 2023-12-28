from cs50 import get_string


def main():
    # Get input text from user
    inputTxt = get_string("Text: ")

    # Count the number or letters
    letterCount = 0
    for letter in inputTxt:
        if letter.isalpha():
            letterCount += 1

    # count the number of words
    wordCount = len(inputTxt.split())

    # count the number of sentences
    sentenceCount = inputTxt.count(".") + inputTxt.count("?") + inputTxt.count("!")

    # apply coleman liau index
    grade = round(0.0588 * (100 * letterCount/wordCount) - 0.296 * (100 * sentenceCount/wordCount) - 15.8)

    # print grade level
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade: {grade}")


main()