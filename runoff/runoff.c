#include <cs50.h>
#include <math.h>
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

    // preferences[voter][rank] = i;
    // printf("name: %s\n", candidates[0].name);
    // printf("votes: %i\n", candidates[0].votes);
    // printf("pref: %s\n", candidates[preferences[0][0]].name);
    // printf("pref 2: %s\n", candidates[preferences[0][1]].name);
    // printf("pref 3: %s\n\n", candidates[preferences[0][2]].name);

    // printf("name: %s\n", candidates[1].name);
    // printf("votes: %i\n", candidates[1].votes);
    // printf("pref: %s\n", candidates[preferences[1][0]].name);
    // printf("pref 2: %s\n", candidates[preferences[1][1]].name);
    // printf("pref 3: %s\n\n", candidates[preferences[1][2]].name);

    // printf("name: %s\n", candidates[2].name);
    // printf("votes: %i\n", candidates[2].votes);
    // printf("pref: %s\n", candidates[preferences[2][0]].name);
    // printf("pref 2: %s\n", candidates[preferences[2][1]].name);
    // printf("pref 3: %s\n", candidates[preferences[2][2]].name);

    int x = 0;
    // Keep holding runoffs until winner exists
    while (x != MAX_VOTERS)
    {
        // Calculate votes given remaining candidates
        tabulate();
        // printf("votes 1: %i\n", candidates[0].votes);
        // printf("votes 2: %i\n", candidates[1].votes);
        // printf("votes 3: %i\n", candidates[2].votes);

        x++;

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
    // voter - Current voter
    // rank - Current rank (rank 1 = 0; rank 2 = 1)
    // name - Name of candidate

    // preferences[i][j] is jth preference for voter i
    // int preferences[MAX_VOTERS][MAX_CANDIDATES];

    for (int i = 0; candidate_count > i; i++)
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
    for (int v = 0; voter_count > v; v++)
    {
        for (int r = 0; r < candidate_count; r++)
        {
            int voter_preference = preferences[v][r];
            if (candidates[voter_preference].eliminated == false)
            {
                candidates[voter_preference].votes++;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // If any candidate has more than half the vote, print their name and return tre
    // If nobody has won the election yet, return false

    int majority = voter_count / 2;
    for (int i = 0; candidate_count > i; i++)
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
int find_min(void)
{
    // Return the minumum number of votes of anyone still in the election
    int current_min = candidates[0].votes; // MAX_VOTERS
    for (int i = 0; candidate_count > i; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < current_min)
        {
            current_min = candidates[i].votes;
        }
    }

    return current_min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Accepts the minumum number of votes min as input
    // Returns true if the election is tied between all remaining candidates, and returns false
    // otherwise

    for (int i = 0; candidate_count > i; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Eliminate anyone still in the race who has the min number of votes
    for (int i = 0; candidate_count > i; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
