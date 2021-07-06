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
    // For evey vote, loop through the candidates and use strcmp:
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winners[candidate_count];
    int highest_votes = 0;
    int next_winner;
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

    winners[0] = highest_voted;
    if (winners[0] >= 0)
    {
        next_winner = 1;
    }

    // rerun loop for possible ties:
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_votes == candidates[i].votes && i != highest_voted)
        {
            winners[next_winner] = i;
            next_winner += 1;
        }
    }

    // finally, print the winner(s), if any:
    for (int i = 0; i < next_winner; i++)
    {
        if (winners[i] >= 0)
        {
            printf("%s\n", candidates[winners[i]].name);
        }
    }

    return;
}