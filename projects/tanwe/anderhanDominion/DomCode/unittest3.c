#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TEST_HAND	10

int main()
{
	srand(time(NULL));
	struct gameState* testState = malloc(sizeof(struct gameState));
	int seed = 1000;
    int numPlayer = 2;
    int r;
	int i, j;
	long passFailFlags = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->handCount[0] = TEST_HAND;
	for(i = 0; i < TEST_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	testState->coins = -1;
	updateCoins(0, testState, 0);
	
	if(testState->coins < 0){
		printf("Function updateCoins failed to update coin values\n");
		passFailFlags |= 1 << 0;
	}
	else if(testState->coins == 0)
	{
		printf("Function updateCoins successfully updated coin values\n");
	}
	else
	{
		printf("Function updateCoins erroneously updated coin values\n");
		passFailFlags |= 1 << 1;
	}
	for(i = 0; i < 2; i++)
	{
		j = rand()%TEST_HAND;
		if(testState->hand[0][j] == curse)
		{
			testState->hand[0][j] = copper;
		}
		else
		{
			i--;
		}
	}
	updateCoins(0, testState, 0);
	if(testState->coins < 0)
	{
		printf("Function updateCoins failed to update coin values\n");
		passFailFlags |= 1 << 0;
	}
	else if(testState->coins == 2)
	{
		printf("Function updateCoins successfully detected copper cards\n");
	}
	else
	{
		printf("Function updateCoins did not detect copper cards\n");
		passFailFlags |= 1 << 1;
	}
	for(i = 0; i < TEST_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	
	
	for(i = 0; i < 2; i++)
	{
		j = rand()%TEST_HAND;
		if(testState->hand[0][j] == curse)
		{
			testState->hand[0][j] = silver;
		}
		else
		{
			i--;
		}
	}
	updateCoins(0, testState, 0);
	if(testState->coins < 0)
	{
		printf("Function updateCoins failed to update coin values\n");
		passFailFlags |= 1 << 0;
	}
	else if(testState->coins == 4)
	{
		printf("Function updateCoins successfully detected silver cards\n");
	}
	else
	{
		printf("Function updateCoins did not detect silver cards\n");
		passFailFlags |= 1 << 2;
	}
	for(i = 0; i < TEST_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	
	for(i = 0; i < 2; i++)
	{
		j = rand()%TEST_HAND;
		if(testState->hand[0][j] == curse)
		{
			testState->hand[0][j] = gold;
		}
		else
		{
			i--;
		}
	}
	updateCoins(0, testState, 0);
	if(testState->coins < 0)
	{
		printf("Function updateCoins failed to update coin values\n");
		passFailFlags |= 1 << 0;
	}
	else if(testState->coins == 6)
	{
		printf("Function updateCoins successfully detected gold cards\n");
	}
	else
	{
		printf("Function updateCoins did not detect gold cards\n");
		passFailFlags |= 1 << 3;
	}
	for(i = 0; i < TEST_HAND; i++)
	{
		testState->hand[0][i] = curse;
	}
	
	for(i = 0; i < 2; i++)
	{
		j = rand()%TEST_HAND;
		if(testState->hand[0][j] == curse)
		{
			testState->hand[0][j] = copper;
		}
		else
		{
			i--;
		}
	}
	
	for(i = 0; i < 2; i++)
	{
		j = rand()%TEST_HAND;
		if(testState->hand[0][j] == curse)
		{
			testState->hand[0][j] = silver;
		}
		else
		{
			i--;
		}
	}
	
	for(i = 0; i < 2; i++)
	{
		j = rand()%TEST_HAND;
		if(testState->hand[0][j] == curse)
		{
			testState->hand[0][j] = gold;
		}
		else
		{
			i--;
		}
	}
	updateCoins(0, testState, 0);
	if(testState->coins < 0)
	{
		printf("Function updateCoins failed to update coin values\n");
		passFailFlags |= 1 << 0;
	}
	else if(testState->coins == 12)
	{
		printf("Function updateCoins successfully detected all treasure cards\n");
	}
	else
	{
		printf("Function updateCoins did not detect all treasure cards\n");
		passFailFlags |= 1 << 4;
	}
	updateCoins(0, testState, 2);
	if(testState->coins < 0)
	{
		printf("Function updateCoins failed to update coin values\n");
		passFailFlags |= 1 << 0;
	}
	else if(testState->coins == 14)
	{
		printf("Function updateCoins successfully detected bonus treasure\n");
	}
	else
	{
		printf("Function updateCoins did not detect bonus treasure\n");
		passFailFlags |= 1 << 5;
	}

	printf("\n");
	if(passFailFlags)
	{
		printf("Test Failed with Code 0x%08X\n", (int)passFailFlags);
	}
	else
	{
		printf("All Tests Successful!\n");
	}
	printf("\n");
	return 0;
}
