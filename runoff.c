// Runoff is a process in which voters vote for candidates using order of preference. Say there are three candidates: Alice, Bob, and Charlie. A voter can vote for each candidate in
// order of a preference. For example, Voter 1 might vote as follows: 1. Alice 2. Bob 3. Charlie. Voter 2 might vote 1. Bob 2. Alice 3. Charlie. Unless any one candidate gets the
// majority of the vote, there is clearly a more complex way to confirm a winner than a 'first-past-the-post' system. This program determines a winner for a variety of situations.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
} candidate;

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

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Look for candidate called {name}
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop through each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Loop through each voter's candidate list
        for (int j = 0; j < candidate_count; j++)
        {
            // If the preferred candidate has not been eliminated, increase
            // vote by 1, otherwise go to the next preferred candidate
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
            continue;
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate what the majority vote is
    int majority = (voter_count / 2) + 1;

    // Loop through 'candidates' and find out the number of
    // votes for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Sort candidates from lowest to highest in terms of votes (Bubble Sort)
    bool swapped;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        swapped = false;
        candidate temp;
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

        // If no two elements were swapped by inner loop,
        // then break from inner loop
        if (swapped == false)
            break;
    }

    // Return the minimum number of votes a candidate has
    int min = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // Since 'Candidates' is in order, check if ith element is NOT
        // eliminated. Therefore, it should be the min.
        if (!candidates[i].eliminated)
        {
            min = candidates[i].votes;
            break;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Create variables that will compare the number
    // of candidates still in the race and have the min vote
    // and the number of candidates left in the race with ANY
    // number of votes.
    int min_count_still_in = 0;
    int candidates_left = candidate_count;

    // Loop through candidates to count for the above vars.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            min_count_still_in++;
        }
        if (candidates[i].eliminated)
        {
            candidates_left--;
        }
    }

    // if # of candidates left is equal to the
    // # of candidates left WITH the min # of votes
    // return true
    if (min_count_still_in == candidates_left)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Eliminate candidates with the min number of votes and lower.
        if (candidates[i].votes <= min)
        {
            candidates[i].eliminated = true;
        }
    }
}
