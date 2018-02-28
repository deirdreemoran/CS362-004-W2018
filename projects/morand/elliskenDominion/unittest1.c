//unittest1.c
// Name: Deirdre Moran
// Function:  Tests the buyCard() function


/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
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
    struct gameState G, testG;
    int buys;
 	int coinage = 1000;

    printf ("TESTING buyCard():\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game

    for (p = 0; p < numPlayer; p++)
    {
		for (buys = 20; buys >= 0; buys--)//check multiple buys fown to zero buys
		{
			for (kCard = 0; kCard < 10; kCard++) // for each kingdom card
			{
#if (NOISY_TEST == 1)
	printf("----------------- Testing buyCard() ----------------\n\n");
		           printf("Test player %d who wants to buy card %d. \n", p, k[kCard]);
#endif
	               // G.handCount[p] = handCount; // set the number of cards on hand
	                G.coins = coinage;
	                G.numBuys = buys;
	                // copy the game state to a test case
					memcpy(&testG, &G, sizeof(struct gameState));
	                // test case buys card
	                buyCard(k[kCard], &testG);

					if (G.numBuys < 1 ){
					// ----------- TEST 1: Testing numBuys stays the same (numBuys < 1 --------------
					myAssert(testG.numBuys == G.numBuys, __FILE__, __LINE__);
#if (NOISY_TEST == 1)
					printf("TEST 1:  Testing numBuys stays the same if numBuys < 1\n");
					printf("numBuys = %d, Expected = %d \n", testG.numBuys, G.numBuys);
#endif
					}
					// ----------- TEST 2: Testing if card supply count stays the same if supply is empty --------------
					else if (supplyCount(k[kCard], &G) < 1){
						myAssert(testG.supplyCount[k[kCard]] == G.supplyCount[k[kCard]], __FILE__, __LINE__);
#if (NOISY_TEST == 1)
						printf("TEST 2:  Testing if card supply count stays the same if supply is empty\n");
						printf("supplyCount = %d, Expected = %d \n", testG.supplyCount[k[kCard]], G.supplyCount[k[kCard]]);
#endif
					}
					// ----------- TEST 3: Testing if coins stay the same if cost of card is greater than coins --------------
					else if (G.coins < getCost(k[kCard])){
						myAssert(testG.coins == G.coins, __FILE__, __LINE__);
#if (NOISY_TEST == 1)
						printf("TEST 3: TEST 3: Testing if coins stay the same if cost of card is greater than coins  \n");
						printf("coins = %d, Expected = %d \n", testG.coins, G.coins);
#endif
					}
#if (NOISY_TEST == 1)
					// ----------- TEST 4: Testing changes in supplyCount, numBuys, and coins when prerequisites to buy card are met --------------

					else{
						printf("TEST 4: Testing changes in supplyCount, numBuys, and coins when prerequisites to buy card are met");
						myAssert(testG.supplyCount[k[kCard]] == G.supplyCount[k[kCard]] - 1, __FILE__, __LINE__);
						myAssert(testG.numBuys == G.numBuys - 1, __FILE__, __LINE__);
						myAssert(testG.coins == G.coins - getCost(k[kCard]), __FILE__, __LINE__);
						printf("supplyCount = %d, Expected = %d \n", testG.supplyCount[k[kCard]], G.supplyCount[k[kCard]] - 1);
						printf("numBuys = %d, Expected = %d \n", testG.numBuys, G.numBuys - 1);
						printf("coins = %d, Expected = %d \n", testG.coins, G.coins - getCost(k[kCard]));
#endif
						memcpy(&G, &testG, sizeof(struct gameState));
		            }
			}
		}
	}

	printf("All tests passed!\n");
	return 0;
}
