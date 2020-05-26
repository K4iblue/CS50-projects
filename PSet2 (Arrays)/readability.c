// Coleman-Liau index formula:
// index = 0.0588 * L - 0.296 * S - 15.8
// "L" = average number of letters per 100 words in a text
// "S" = average number of sentences per 100 words in a text

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Prototypes
int coleMan(int letters, int words, int sentences);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Ask user for a text to check
    string inputText = get_string("Text: ");

    int grade = coleMan(count_letters(inputText), count_words(inputText), count_sentences(inputText));

    // Print how many Letters, Words, Sentences are in the given String
    printf("Letters: %d\n", count_letters(inputText));
    printf("Words: %d\n", count_words(inputText));
    printf("Sentences: %d\n", count_sentences(inputText));

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

}

int coleMan(int letters, int words, int sentences)
{
    // Need to get the average number of letters per 100 words
    // We need to cast letters to a float
    float L = (((float)letters * 100) / words);

    // Need to get the average number of sentences per 100 words
    // We need to cast sentences to a float
    float S = (((float)sentences * 100) / words);

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

// Count the letters in a given string
// Does not count digits as letters
int count_letters(string text)
{
    int letterCount = 0;

    for (int i = 0; i <= strlen(text); i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letterCount++;
        }
    }
    return letterCount;
}


// Count the words in a given string
// Words are a string of characters that ends with a space (equal to "\0") in between words
int count_words(string text)
{
    int wordCount = 0;

    if (isalpha(text[0]))
    {
        wordCount++;
    }

    for (int i = 0; i <= strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            wordCount++;
        }
    }
    return wordCount;
}

// Count the sentences in a given string.
// For this problem set: A sentence is a string of words that ends with an ".", "!" or "?"
int count_sentences(string text)
{
    int sentencesCount = 0;

    for (int i = 0; i <= strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentencesCount++;
        }
    }
    return sentencesCount;
}