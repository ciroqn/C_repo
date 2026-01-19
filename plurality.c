// Algorithm to determine winner(s) of first-past-the-post electoral system.

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
} candidate;

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

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop through candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare if input, 'name', is in the candidates array
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Add a vote to relevant candidate
            candidates[i].votes++;
            return true;
        }
    }
    // Returns false IF name not found
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Bubble sort to arrange candidates in order of votes
    bool swapped;
    // Store candidate in temp in order to swap indices if bigger
    candidate temp;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        swapped = false;
        // Inner loop used to compare each pair of number n-1 times
        for (int j = 0; j < candidate_count - i - 1; j++)
        {
            if (candidates[j].votes > candidates[j + 1].votes)
            {
                temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
                swapped = true;
            }
        }

        // If no two elements swapped in inner loop, then break
        if (swapped == false)
            break;
    }

    // Create loop and start from the end of the SORTED 'candidates' to see if
    // there is more than one winner. 'winner_num' stores number of winners
    int winner_num = 1;
    for (int i = candidate_count - 1; i > 0; i--)
    {
        if (candidates[i].votes == candidates[i - 1].votes)
        {
            winner_num++;
        }
    }

    // print name of winner[s]
    if (winner_num > 1)
    {
        // Prints the last x candidates who have the max tied votes
        for (int i = candidate_count - 1; i >= candidate_count - winner_num; i--)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    else
    {
        printf("%s\n", candidates[candidate_count - 1].name);
    }
}
