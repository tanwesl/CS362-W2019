#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "randTestUtils.h"

#define NOISY 0

int main(void)
{
	int passFailFlags = 0;
	struct gameState* testState = malloc(sizeof(struct gameState));
	struct gameState pretestState;
	time_t testTime = time(NULL);
	int result;
	
	while(difftime(time(NULL),testTime) < 30){
		initRandom(testState);
#if NOISY
		printState(testState, 0);
#endif
		pretestState = *testState;
		result = cardEffect(village, 0, 0, 0, testState, rand()%testState->handCount[testState->whoseTurn], 0);
		assert(!result);
#if NOISY
		printState(testState, 1);
#endif
		if(pretestState.deckCount[pretestState.whoseTurn] + pretestState.discardCount[pretestState.whoseTurn] == 0){
			if(testState->handCount[pretestState.whoseTurn] != pretestState.handCount[pretestState.whoseTurn] - 1){
#if NOISY
				printf("Incorrect number of cards in player's hand.\n");
#endif
				passFailFlags |= 1 << 0;
			}
		}
		else{
			if(testState->handCount[pretestState.whoseTurn] != pretestState.handCount[pretestState.whoseTurn]){
#if NOISY
				printf("Incorrect number of cards in player's hand; drew from an empty deck.\n");
#endif
				passFailFlags |= 1 << 1;
			}
		}
		if(testState->numActions != pretestState.numActions + 2){
#if NOISY
			printf("Incorrect number of player actions added.\n");
#endif
			passFailFlags |= 1 << 2;
		}
	}
	if(passFailFlags){
		printf("Test Failed with Error Code 0x%08X\n", passFailFlags);
	}
	else{
		printf("All tests successful.\n");
	}
	return 0;
}
