//unittest4.c
// Name: Deirdre Moran
// Function:  Tests the gainCard() function

/*
 * Include the following lines in your make__FILE__:
 *
 * unittest1: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int p;
    int kCard;
    int k[10] = {adventurer, council_room, feast, gardens, mine
	               , remodel, smithy, village, baron, great_hall};
	int flag;
	//added card for [whoseTurn] current player:
	  // toFlag = 0 : add to discard
	  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

    struct gameState G, testG;

    printf ("----------------------TESTING gainCard()-------------------------\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state

    for (p = 0; p < numPlayer; p++)
    {
		for (flag = 0; flag < 3; flag++)
		{
			for (kCard = 0; kCard < 10; kCard++)
			{
				initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
	                printf("Test player %d who gains card %d with flag %d. \n", p, k[kCard], flag);
#endif
	                // copy the game state to a test case
					memcpy(&testG, &G, sizeof(struct gameState));
	                // test case gains card
	                gainCard(k[kCard], &testG, flag, p);

					if(flag == 1){
					myAssert(k[kCard] == testG.deck[p][testG.deckCount[p] - 1], __FILE__, __LINE__);
					myAssert(G.deckCount[p] == testG.deckCount[p] - 1, __FILE__, __LINE__);
					myAssert(testG.supplyCount[k[kCard]] + 1 == G.supplyCount[k[kCard]], __FILE__, __LINE__);
#if (NOISY_TEST == 1)
					printf("testG.[k[kCard]] = %d, Expected = %d \n", k[kCard], testG.deck[p][testG.deckCount[p] - 1]);
					printf("testG.deckCount[p] = %d, Expected = %d \n", testG.deckCount[p], G.deckCount[p] + 1);
					printf("testG.supplyCount[k[kCard]] = %d, Expected = %d \n", testG.supplyCount[k[kCard]] + 1, G.supplyCount[k[kCard]]);
#endif
				}

				if(flag == 2){

					myAssert(k[kCard] == testG.hand[p][testG.handCount[p] - 1], __FILE__, __LINE__);
					myAssert(G.handCount[p] == testG.handCount[p] - 1, __FILE__, __LINE__);
					myAssert(testG.supplyCount[k[kCard]] + 1 == G.supplyCount[k[kCard]], __FILE__, __LINE__);
#if (NOISY_TEST == 1)
					printf("testG.[k[kCard]] = %d, Expected = %d \n", k[kCard], testG.hand[p][testG.handCount[p] - 1]);
					printf("testG.handCount[p] = %d, Expected = %d \n", testG.handCount[p], G.handCount[p] + 1);
					printf("testG.supplyCount[k[kCard]] = %d, Expected = %d \n", testG.supplyCount[k[kCard]] + 1, G.supplyCount[k[kCard]]);
#endif
				}


				if(flag == 0){
					myAssert(k[kCard] == testG.discard[p][testG.discardCount[p] - 1], __FILE__, __LINE__);
					myAssert(G.discardCount[p] == testG.discardCount[p] - 1, __FILE__, __LINE__);
					myAssert(testG.supplyCount[k[kCard]] + 1 == G.supplyCount[k[kCard]], __FILE__, __LINE__);
#if (NOISY_TEST == 1)
					printf("testG.[k[kCard]] = %d, Expected = %d \n", k[kCard], testG.discard[p][testG.discardCount[p] - 1]);
					printf("testG.discardCount[p] = %d, Expected = %d \n", testG.discardCount[p], G.discardCount[p] + 1);
					printf("testG.supplyCount[k[kCard]] = %d, Expected = %d \n", testG.supplyCount[k[kCard]] + 1, G.supplyCount[k[kCard]]);
				}
#endif

					memcpy(&G, &testG, sizeof(struct gameState));

			}
		}
	}

	printf("All tests passed!\n");
	return 0;
}
