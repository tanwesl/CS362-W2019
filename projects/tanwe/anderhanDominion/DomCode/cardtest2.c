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
	int origHandCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState* testState = malloc(sizeof(struct gameState));	

	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	assert(testState->handCount[0] > 0);
	assert(testState->deckCount[0] + testState->discardCount[0] >=3);
	origHandCount = testState->handCount[0];
	testState->hand[0][testState->handCount[0]-1] = smithy;
	r = cardEffect(smithy, 0, 0, 0, testState, testState->handCount[0]-1, 0);
	assert(!r);
	if(testState->handCount[0] == origHandCount + 2)
	{
		printf("Smithy drew the correct number (3) of cards when called from the top of the deck\n");
	}
	else
	{
		printf("Smithy drew an incorrect number (%d) of cards when called from the top of the deck\n", testState->handCount[0] - origHandCount + 1);
		passFailFlags |= 1 << 0;
	}

	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	assert(testState->handCount[0] > 0);
	assert(testState->deckCount[0] + testState->discardCount[0] >=3);
	origHandCount = testState->handCount[0];
	testState->hand[0][0] = smithy;
	r = cardEffect(smithy, 0, 0, 0, testState, testState->handCount[0]-1, 0);
	assert(!r);
	if(testState->handCount[0] == origHandCount + 2)
	{
		printf("Smithy drew the correct number (3) of cards when called from the bottom of the deck\n");
	}
	else
	{
		printf("Smithy drew an incorrect number (%d) of cards when called from the bottom of the deck\n", testState->handCount[0] - origHandCount + 1);
		passFailFlags |= 1 << 1;
	}

	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->whoseTurn=0;
	assert(testState->handCount[0] > 0);
	origHandCount = testState->handCount[0];
	testState->hand[0][0] = smithy;
	testState->deckCount[0] = 2;
	testState->discardCount[0] = 0;
	r = cardEffect(smithy, 0, 0, 0, testState, testState->handCount[0]-1, 0);
	assert(!r);
	if(testState->handCount[0] == origHandCount + 1)
	{
		printf("Smithy drew fewer cards when not enough were available\n");
	}
	else
	{
		printf("Smithy drew more cards than were available\n");
		passFailFlags |= 1 << 2;
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
