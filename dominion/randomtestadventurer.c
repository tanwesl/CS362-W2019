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
	int i;
	int treasureCounter;

	while(difftime(time(NULL),testTime) < 30){
		treasureCounter = 0;
		initRandom(testState);
		pretestState = *testState;
		for(i = 0; i < pretestState.deckCount[pretestState.whoseTurn]; i++){
			if((pretestState.deck[pretestState.whoseTurn][i] == gold) || (pretestState.deck[pretestState.whoseTurn][i] == silver) || (pretestState.deck[pretestState.whoseTurn][i] == copper)){
				treasureCounter++;
			}
			if(treasureCounter == 2){
				break;
			}
		}
		if(treasureCounter < 2){
			for(i = 0; i < pretestState.discardCount[pretestState.whoseTurn]; i++){
				if((pretestState.discard[pretestState.whoseTurn][i] == gold) || (pretestState.discard[pretestState.whoseTurn][i] == silver) || (pretestState.discard[pretestState.whoseTurn][i] == copper)){
					treasureCounter++;
				}
				if(treasureCounter == 2){
					break;
				}
			}
		}
#if NOISY
		printState(testState, 0);
		printf("%d treasure found in deck + discard.\n", treasureCounter);
#endif

		result = cardEffect(adventurer, 0, 0, 0, testState, rand()%testState->handCount[testState->whoseTurn], 0);
		assert(!result);
		updateCoins(pretestState.whoseTurn, testState, 0);
#if NOISY
		printState(testState, 1);
#endif
		if(testState->handCount[pretestState.whoseTurn] != pretestState.handCount[pretestState.whoseTurn] + treasureCounter - 1){
#if NOISY
			printf("Incorrect number of cards in player's hand.\n");
#endif
			passFailFlags |= 1 << 0;
		}
		for(i = 0; i < treasureCounter; i++){
			if((testState->hand[testState->whoseTurn][testState->handCount[pretestState.whoseTurn] - (i + 1)] != gold) && (testState->hand[testState->whoseTurn][testState->handCount[pretestState.whoseTurn] - (i + 1)] != silver) && (testState->hand[testState->whoseTurn][testState->handCount[pretestState.whoseTurn] - (i + 1)] != copper)){
#if NOISY
				printf("New card in hand is not a treasure card.\n");
#endif
				passFailFlags |= 1 << 1;
			}
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
