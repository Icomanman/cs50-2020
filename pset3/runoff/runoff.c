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
    // For evey vote, loop through the candidates and use strcmp:
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // candidates[i].votes += 1;
            // record the input into the preferences matrix:
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        // get the first rank:
        int voted_candidate = preferences[i][0];
        // count the respective vote towards the candidate of first rank:
        candidates[voted_candidate].votes += 1;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // int ties[candidate_count];
    // int next_winner;
    int highest_votes = 0;
    int highest_voted;

    for (int i = 0; i < candidate_count; i++)
    {
        // get the highest voted candidate:
        if (highest_votes < candidates[i].votes)
        {
            highest_votes = candidates[i].votes;
            // get the index of highest voted candidate:
            highest_voted = i;
        }
    }

    // ties[0] = highest_voted;
    // if (ties[0] >= 0)
    // {
    //     next_winner = 1;
    // }

    // rerun loop for possible ties:
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_votes == candidates[i].votes && i != highest_voted)
        {
            // there's at least a tie. So maybe there's no need to proceed?
            return false;
            // ties[next_winner] = i;
            // next_winner += 1;
        }
        else
        {
            // if there's no tie, then there's a winner
            printf("%s\n", candidates[highest_voted].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // this is a sorting problem from the lecture :)
    int lowest_votes = 0;
    int lowest_voted = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
        {
            continue;
        }

        // get the lowest voted candidate:
        if (candidates[lowest_voted].votes > candidates[i].votes)
        {
            lowest_votes = candidates[i].votes;
            // get the index of lowest voted candidate:
            lowest_voted = i;
        }
    }
    return lowest_voted;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int ties[candidate_count];
    int next_winner = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            ties[next_winner] = i;
            next_winner += 1;
        }
    }

    if (next_winner > 0)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // eliminate the candidates with votes equal to min:
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

// 2hrs+ and counting: 08 July 2021