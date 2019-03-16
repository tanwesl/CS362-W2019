#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main(){
	long passFailFlags = 0;
	int seed = 1000;
	int numPlayer = 2;
	int r;
	int origHandCount, origActionCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState* testState = malloc(sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	assert(testState->handCount[0] > 0);
	origHandCount = testState->handCount[0];
	origActionCount = testState->numActions;
	testState->hand[0][0] = great_hall;
	r = cardEffect(great_hall, 0, 0, 0, testState, 0, 0);
	assert(!r);
	if(testState->handCount[0] == origHandCount)
	{
		printf("Great Hall successfully drew a card\n");
	}
	else
	{
		printf("Great Hall failed to draw a card\n");
		passFailFlags |= 1 << 0;
	}
	if(testState->numActions == origActionCount + 1)
	{
		printf("Great Hall successfully added an action\n");
	}
	else
	{
		printf("Great Hall failed to add an action\n");
		passFailFlags |= 1 << 1;
	}

	printf("\n");
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
