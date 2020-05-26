#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// #######################################################################
// Code above this line was given by the CS50 Staff
// I only needed to add the functions below
// #######################################################################


// Record preference if vote is valid
// Iterate over all candidates
// If "name" is equal to "candidate[i].name"
// Update preferences[voter][rank] and return true
// Else return false
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((strcmp(name, candidates[i].name)) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// Need a variable so we can get the right candidate, we call it "j"
// Iterate over all voters
// If the candidate is eliminated we increase "j" so we jump to the next candidate that is not eliminated
// If candidate is not eliminated, set preferences
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        
        while (candidates[preferences[i][j]].eliminated == true)
        {
            j++;
        }
        candidates[preferences[i][j]].votes++;
    }
    return;
}

// Print the winner of the election, if there is one
// We need a variable to store the number of votes we need to have a majority
// Round majority to get a safe number
// Loop over all candidates
// If a candidate has more votes than "majority", they won and we print their name, return true;
// Else return false
bool print_winner(void)
{
    int majority = round(voter_count / 2);
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
// We need a variable to store the lowest number of votes
// Set "lowestVotes" equal to the votes of "candidates[0].votes", because we check them first anyway
// If the candidate is not eliminated and has less votes than "lowestVotes"
// Set "lowestVotes" to "candidate[i].votes"
// If finished return "lowestVotes"
int find_min(void)
{
    int lowestVotes = candidates[0].votes;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].eliminated == false) && (lowestVotes > candidates[i].votes))
        {
            lowestVotes = candidates[i].votes;
        }
    }
    return lowestVotes;
}

// Return true if the election is tied between all candidates, false otherwise
// We need two new variables "notElimniated" and "countCandidates"
// Loop over all candidates
// If they are not Eliminated increase "notEliminated" by 1
// If "candidates[i].votes" are equal to the "lowestVotes" increase "counter"
// Compare "notEliminated" and "counter", if equal we have a tie, return true
// Else return false
bool is_tie(int min)
{
    int notEliminated = 0;
    int counter = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            notEliminated++;
            if (candidates[i].votes == min)
            {
                counter++;
            }
        }
    }
    
    if (notEliminated == counter)
    {
        return true;
    }
    
    return false;
}

// Eliminate the candidate (or candidiates) in last place
// Iterate over all candidates that are not eliminated yet
// If their number of votes is equal to "min" eliminate them
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes <= min)
        {
            candidates[i].eliminated = true;
        }
    }
    
    return;
}
