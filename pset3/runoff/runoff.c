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
        for (int j = 0; j < candidate_count; j++)
        {
            // get the jth rank, starting from rank 1 (index 0):
            int voted_candidate = preferences[i][j];
            // count the respective vote towards the candidate of first rank:
            if (candidates[voted_candidate].eliminated == false)
            {
                candidates[voted_candidate].votes += 1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int highest_votes = 0;
    int highest_voted;

    // this seems to be some kind of selection sort...
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // get the highest voted candidate:
        if (candidates[i].votes > candidates[i + 1].votes && candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
            // get the index of highest voted candidate:
            highest_voted = i;
        }
        else if (candidates[i + 1].votes > candidates[i].votes && candidates[i + 1].votes > highest_votes)
        {
            highest_votes = candidates[i + 1].votes;
            // get the index of highest voted candidate:
            highest_voted = i + 1;
        }
    }

    // rerun loop for possible ties:
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_votes == candidates[i].votes && i != highest_voted)
        {
            // there's at least a tie. So maybe there's no need to proceed?
            return false;
        }
        else if (highest_votes > (voter_count / 2))
        {
            // if there's no tie and a candidate gets the majority of votes, then there's a winner
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
    // assume the first candidate has the lowest vote:
    int lowest_voted = 0;
    int lowest_votes = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        // check for candidates with 0 votes (shortcut):
        if (candidates[i].votes == 0)
        {
            return 0;
        }

        if (i == 0)
        {
            continue;
        }

        // get the lowest voted candidate:
        if (candidates[i].votes < lowest_votes && candidates[i].eliminated == false)
        {
            lowest_votes = candidates[i].votes;
            // get the index of lowest voted candidate:
            lowest_voted = i;
        }
    }
    return lowest_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int rem_candidates[candidate_count];
    int rem_count = candidate_count;
    int ties = 0;
    int curr_score = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        // mark the candidates:
        if (candidates[i].eliminated == true && min >= candidates[i].votes)
        {
            rem_candidates[i] = 0;
            rem_count -= 1;
        }
        else
        {
            rem_candidates[i] = 1;
        }
    }

    // loop through the remaining canditates:
    for (int j = 0; j < candidate_count; j++)
    {

        if (rem_candidates[j] == 1 && curr_score == 0)
        {
            curr_score = candidates[j].votes;
        }
        else if (rem_candidates[j] == 1)
        {
            if (curr_score == candidates[j].votes)
            {
                ties += 1;
            }
        }
    }
    if (ties == (rem_count - 1))
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

// 4.5hrs+ and counting: 10 July 2021