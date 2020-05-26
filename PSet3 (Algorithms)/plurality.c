#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// #######################################################################
// Code above this line was given by the CS50 Staff
// I only needed to add the functions below
// #######################################################################

// Update vote totals given a new vote
bool vote(string name)
{
    printf("You voted for: %s\n", name);

    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare if the given string is a valid candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            printf("Vote Count: %d\n", candidates[i].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Store the number of votes, for the most voted candidate while counting all votes
    int mostVotes = 0;

    // Store the name of the current winner, while counting the votes
    string winnerName;

    // Loop over all candidates and store the name of the candidate with the most votes in "winnerName" 
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= mostVotes)
        {
            mostVotes = candidates[i].votes;
            winnerName = candidates[i].name;
        }
    }
    
    // Loop of all candidates and print the name of every candidate that has the same amount of votes as in "mostVotes"
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == mostVotes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}
