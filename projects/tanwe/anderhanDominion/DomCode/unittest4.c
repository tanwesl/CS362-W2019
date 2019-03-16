#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main()
{
	long passFailFlags = 0;
	int seed = 1000;
	int numPlayer = 2;
	int r;
	int discardVal, deckVal, handVal;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState* testState = malloc(sizeof(struct gameState));

	//Test the discard pile functionality
	//Empty discard
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 0, 0);
	if(testState->discard[0][0] == copper)
	{
		printf("Function gainCard correctly adds to empty discard\n");
	}
	else
	{
		printf("Function gainCard fails to add to empty discard\n");
		passFailFlags |= 1 << 3;
	}
	if(testState->discardCount[0] == discardVal+1)
	{
		printf("Function gainCard correctly adds to empty discard counter\n");
	}
	else
	{
		printf("Function gainCard fails to add to empty discard counter\n");
		passFailFlags |= 1 << 4;
	}
	if(testState->deckCount[0] != deckVal)
	{
		printf("Function gainCard incorrectly adds to deck counter\n");
		passFailFlags |= 1 << 0;
	}
	if(testState->handCount[0] != handVal)
	{
		printf("Function gainCard incorrectly adds to hand counter\n");
		passFailFlags |= 1 << 1;
	}

	//Partially-filled discard
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = (int)floor(MAX_DECK/2);
	testState->discard[0][(int)floor(MAX_DECK/2)] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 0, 0);
	if(testState->discard[0][(int)floor(MAX_DECK/2)] == copper)
	{
		printf("Function gainCard correctly adds to partially-full discard\n");
	}
	else
	{
		printf("Function gainCard fails to add to partially-full discard\n");
		passFailFlags |= 1 << 5;
	}
	if(testState->discardCount[0] == discardVal+1)
	{
		printf("Function gainCard correctly adds to partially-full discard counter\n");
	}
	else
	{
		printf("Function gainCard fails to add to partially-full discard counter\n");
		passFailFlags |= 1 << 6;
	}
	if(testState->deckCount[0] != deckVal)
	{
		printf("Function gainCard incorrectly adds to deck counter\n");
		passFailFlags |= 1 << 0;
	}
	if(testState->handCount[0] != handVal)
	{
		printf("Function gainCard incorrectly adds to hand counter\n");
		passFailFlags |= 1 << 1;
	}

	//Filled discard
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = MAX_DECK;
	testState->discard[0][MAX_DECK] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 0, 0);
	if(!r)
	{
		printf("Function gainCard incorrectly adds to full discard\n");
		passFailFlags |= 1 << 7;
	}
	else
	{
		printf("Function gainCard correctly does not add to full discard\n");
	}
	if(testState->discardCount[0] == discardVal+1)
	{
		printf("Function gainCard incorrectly adds to full discard counter\n");
		passFailFlags |= 1 << 8;
	}
	else
	{
		printf("Function gainCard correctly does not add to full discard counter\n");
	}
	if(testState->deckCount[0] != deckVal)
	{
		printf("Function gainCard incorrectly adds to deck counter\n");
		passFailFlags |= 1 << 0;
	}
	if(testState->handCount[0] != handVal)
	{
		printf("Function gainCard incorrectly adds to hand counter\n");
		passFailFlags |= 1 << 1;
	}

	//Test the deck pile functionality
	//Empty deck
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 1, 0);
	if(testState->deck[0][0] == copper)
	{
		printf("Function gainCard correctly adds to empty discard\n");
	}
	else
	{
		printf("Function gainCard fails to add to empty discard\n");
		passFailFlags |= 1 << 9;
	}
	if(testState->deckCount[0] == deckVal+1)
	{
		printf("Function gainCard correctly adds to empty discard counter\n");
	}
	else
	{
		printf("Function gainCard fails to add to empty discard counter\n");
		passFailFlags |= 1 << 10;
	}
	if(testState->discardCount[0] != discardVal)
	{
		printf("Function gainCard incorrectly adds to discard counter\n");
		passFailFlags |= 1 << 2;
	}
	if(testState->handCount[0] != handVal)
	{
		printf("Function gainCard incorrectly adds to hand counter\n");
		passFailFlags |= 1 << 1;
	}

	//Partially-filled deck
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = (int)floor(MAX_DECK/2);
	testState->deck[0][(int)floor(MAX_DECK/2)] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 1, 0);
	if(testState->deck[0][(int)floor(MAX_DECK/2)] == copper)
	{
		printf("Function gainCard correctly adds to partially-full deck\n");
	}
	else
	{
		printf("Function gainCard fails to add to partially-full deck\n");
		passFailFlags |= 1 << 11;
	}
	if(testState->deckCount[0] == deckVal+1)
	{
		printf("Function gainCard correctly adds to partially-full deck counter\n");
	}
	else
	{
		printf("Function gainCard fails to add to partially-full deck counter\n");
		passFailFlags |= 1 << 12;
	}
	if(testState->discardCount[0] != discardVal)
	{
		printf("Function gainCard incorrectly adds to discard counter\n");
		passFailFlags |= 1 << 2;
	}
	if(testState->handCount[0] != handVal)
	{
		printf("Function gainCard incorrectly adds to hand counter\n");
		passFailFlags |= 1 << 1;
	}

	//Filled deck
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = MAX_DECK;
	testState->deck[0][MAX_DECK] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 1, 0);
	if(!r)
	{
		printf("Function gainCard incorrectly adds to full deck\n");
		passFailFlags |= 1 << 13;
	}
	else
	{
		printf("Function gainCard correctly does not add to full deck\n");
	}
	if(testState->deckCount[0] == deckVal+1)
	{
		printf("Function gainCard incorrectly adds to full deck counter\n");
		passFailFlags |= 1 << 14;
	}
	else
	{
		printf("Function gainCard correctly does not add to full deck counter\n");
	}
	if(testState->discardCount[0] != discardVal)
	{
		printf("Function gainCard incorrectly adds to discard counter\n");
		passFailFlags |= 1 << 2;
	}
	if(testState->handCount[0] != handVal)
	{
		printf("Function gainCard incorrectly adds to hand counter\n");
		passFailFlags |= 1 << 1;
	}

	//Test the hand functionality
	//Empty hand
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 2, 0);
	if(testState->hand[0][0] == copper)
	{
		printf("Function gainCard correctly adds to empty hand\n");
	}
	else
	{
		printf("Function gainCard fails to add to empty hand\n");
		passFailFlags |= 1 << 15;
	}
	if(testState->handCount[0] == handVal+1)
	{
		printf("Function gainCard correctly adds to empty hand counter\n");
	}
	else
	{
		printf("Function gainCard fails to add to empty hand counter\n");
		passFailFlags |= 1 << 16;
	}
	if(testState->deckCount[0] != deckVal)
	{
		printf("Function gainCard incorrectly adds to deck counter\n");
		passFailFlags |= 1 << 2;
	}
	if(testState->discardCount[0] != discardVal)
	{
		printf("Function gainCard incorrectly adds to discard counter\n");
		passFailFlags |= 1 << 0;
	}

	//Partially-filled hand
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = (int)floor(MAX_HAND/2);
	testState->hand[0][(int)floor(MAX_HAND/2)] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 2, 0);
	if(testState->hand[0][0] == copper)
	{
		printf("Function gainCard correctly adds to partially-full hand\n");
	}
	else
	{
		printf("Function gainCard fails to add to partially-full hand\n");
		passFailFlags |= 1 << 17;
	}
	if(testState->handCount[0] == handVal+1)
	{
		printf("Function gainCard correctly adds to partially-full hand counter\n");
	}
	else
	{
		printf("Function gainCard fails to add to partially-full hand counter\n");
		passFailFlags |= 1 << 18;
	}
	if(testState->deckCount[0] != deckVal)
	{
		printf("Function gainCard incorrectly adds to deck counter\n");
		passFailFlags |= 1 << 2;
	}
	if(testState->discardCount[0] != discardVal)
	{
		printf("Function gainCard incorrectly adds to discard counter\n");
		passFailFlags |= 1 << 0;
	}

	//Filled hand
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = MAX_HAND;
	testState->hand[0][MAX_HAND] = 0;
	discardVal = testState->discardCount[0];
	deckVal = testState->deckCount[0];
	handVal = testState->handCount[0];
	r = gainCard(copper, testState, 2, 0);
	if(!r)
	{
		printf("Function gainCard incorrectly adds to full hand\n");
		passFailFlags |= 1 << 18;
	}
	else
	{
		printf("Function gainCard correctly does not add to full hand\n");
	}
	if(testState->handCount[0] == handVal+1)
	{
		printf("Function gainCard incorrectly adds to full hand counter\n");
		passFailFlags |= 1 << 19;
	}
	else
	{
		printf("Function gainCard correctly does not add to full hand counter\n");
	}
	if(testState->deckCount[0] != deckVal)
	{
		printf("Function gainCard incorrectly adds to deck counter\n");
		passFailFlags |= 1 << 2;
	}
	if(testState->discardCount[0] != discardVal)
	{
		printf("Function gainCard incorrectly adds to discard counter\n");
		passFailFlags |= 1 << 0;
	}

	//Try pulling from empty supply
	r = initializeGame(numPlayer, k, seed, testState);
	assert(!r);
	testState->discardCount[0] = 0;
	testState->discard[0][0] = 0;
	testState->deckCount[0] = 0;
	testState->deck[0][0] = 0;
	testState->handCount[0] = 0;
	testState->hand[0][0] = 0;
	testState->supplyCount[copper] = 0;
	r = gainCard(copper, testState, 0, 0);
	if(!r)
	{
		printf("Function gainCard incorrectly draws from empty supply\n");
		passFailFlags |= 1 << 20;
	}
	else
	{
		printf("Function gainCard correctly does not draw from empty supply\n");
	}
	
	printf("\n");
	if(passFailFlags)
	{
		printf("Test Failed with Code 0x%08X\n\n", (int)passFailFlags);
	}
	else
	{
		printf("All Tests Successful!\n\n");
	}
	return 0;
}
