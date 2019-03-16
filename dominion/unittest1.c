#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//Maximum number of supplies that will be empty
//can be greater than 3 at end-of-game given
//active player's turn always ends before game-end
#define MAXEMPTY	5
int main()
{
	//rng seed, inits, etc.
	srand(time(NULL));
	struct gameState* testState = malloc(sizeof(struct gameState));
	int seed = 1000;
    int numPlayer = 2;
    int r;
	int emptyCards[MAXEMPTY];
	int activeCards[17];
	int provinceCount;
	int i, j;
	long passFailFlags = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	
	for(i = 0; i < 10; i++)
	{
		activeCards[i] = k[i];
	}
	
	activeCards[10] = 0;
	activeCards[11] = 1;
	activeCards[12] = 2;
	activeCards[13] = 3;
	activeCards[14] = 4;
	activeCards[15] = 5;
	activeCards[16] = 6;
	
	//set MAXEMPTY different piles that will be empty for testing
	//exclude provinces to separate game-over conditions
	for(i=0; i < MAXEMPTY; i++)
	{
		emptyCards[i]=rand()%17;
		for(j=0; j < MAXEMPTY; j++)
		{
			if(((emptyCards[i] == emptyCards[j]) || (emptyCards[i] == province + 10)) && i!=j){
				i--;
			}
		}
	}
	
	//refill lst with actual cards to be emptied
	for(i=0; i < MAXEMPTY; i++)
	{
		emptyCards[i] = activeCards[emptyCards[i]];
	}
	
	//Test Cases
	provinceCount = testState->supplyCount[province];
	testState->supplyCount[province] = 0;
	if(isGameOver(testState))
	{
		printf("Function isGameOver successfully detected valid Endgame Condition:\n\tProvince Pile Empty\n");
	}
	else
	{
		printf("Function isGameOver failed to detect valid Endgame Condition:\n\tProvince Pile Empty\n");
		passFailFlags |= 1 << 0;
	}
	
	testState->supplyCount[province] = provinceCount;
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver detected false-positive Endgame Condition:\n\tProvince Pile Full\n\tZero Empty Supplies\n");
		passFailFlags |= 1 << 1;
	}
	
	testState->supplyCount[emptyCards[0]] = 0;
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver detected false-positive Endgame Condition:\n\tProvince Pile Full\n\tOne Empty Supplies\n");
		passFailFlags |= 1 << 2;
	}
	
	testState->supplyCount[emptyCards[1]] = 0;
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver detected false-positive Endgame Condition:\n\tProvince Pile Full\n\tTwo Empty Supplies\n");
		passFailFlags |= 1 << 3;
	}
	
	testState->supplyCount[emptyCards[2]] = 0;
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver successfully detected valid Endgame Condition:\n\tProvince Pile Full\n\tThree Empty Supplies\n");
	}
	else
	{
		printf("Function isGameOver failed to detect valid Endgame Condition:\n\tProvince Pile Full\n\tThree Empty Supplies\n");
		passFailFlags |= 1 << 4;
	}
	
	testState->supplyCount[emptyCards[3]] = 0;	
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver successfully detected valid Endgame Condition:\n\tProvince Pile Full\n\tFour Empty Supplies\n");
	}
	else
	{
		printf("Function isGameOver failed to detect valid Endgame Condition:\n\tProvince Pile Full\n\tFour Empty Supplies\n");
		passFailFlags |= 1 << 5;
	}
	
	testState->supplyCount[emptyCards[4]] = 0;
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver successfully detected valid Endgame Condition:\n\tProvince Pile Full\n\tFive Empty Supplies\n");
	}
	else
	{
		printf("Function isGameOver failed to detect valid Endgame Condition:\n\tProvince Pile Full\n\tFive Empty Supplies\n");
		passFailFlags |= 1 << 6;
	}
	
	testState->supplyCount[province] = 0;
	
	if(isGameOver(testState))
	{
		printf("Function isGameOver successfully detected valid Endgame Condition:\n\tProvince Pile Empty\n\tFive Empty Supplies\n");
	}
	else
	{
		printf("Function isGameOver failed to detect valid Endgame Condition:\n\tProvince Pile Empty\n\tFive Empty Supplies\n");
		passFailFlags |= 1 << 7;
	}
	printf("\n");
	//End-of-Test reports
	if(passFailFlags)
	{
		printf("Test Failed with Code 0x%08X\n\n", (int)passFailFlags);
	}
	else
	{
		printf("Test Successful!\n\n");
	}
	
	return 0;
}
