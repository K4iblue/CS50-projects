# Coleman-Liau index formula:
# index = 0.0588 * L - 0.296 * S - 15.8
# "L" = average number of letters per 100 words in a text
# "S" = average number of sentences per 100 words in a text


# Import get_string from cs50
from cs50 import get_string


def main():
    # Ask user for text to check
    inputText = get_string("Text: ")

    # Calculate grade for the given text
    grade = coleMan(count_letters(inputText), count_words(inputText), count_sentences(inputText))

    # Print how many letters, words, sentences are in the given string
    print("Letters: ", count_letters(inputText))
    print("Words: ", count_words(inputText))
    print("Sentences: ", count_sentences(inputText))

    # Print for which grade the given text is appropriate
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade", grade)


def coleMan(letters, words, sentences):
    # Coleman-Liau index
    # Need to get the average number of letters per 100 words
    L = ((letters * 100) / words)

    # Need to get the average number of sentences per 100 words
    S = ((sentences * 100) / words)

    index = round(0.0588 * L - 0.296 * S - 15.8)

    return index


def count_letters(text):
    # Count the letters in a given string
    # Does not count digits as letters
    letterCount = 0

    for c in text:
        if c.isalpha():
            letterCount = letterCount + 1

    return letterCount


def count_words(text):
    # Count the words in a given string
    # Words are a string that ends with a space between words
    wordCount = 0

    wordCount = len(text.split())

    return wordCount


def count_sentences(text):
    # Count the sentences in a given string
    # For this problem set: A sentence is a string of words that ends with an ".", "!" or "?"
    sentencesCount = 0

    for line in text:
        sentencesCount += line.count('.') + line.count('!') + line.count('?')

    return sentencesCount


# Call main function
main()