//unittest2.c
// Name: Deirdre Moran
// Function:  Tests the upDateCoins() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int mix1[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    // array of mixed coppers and golds
    for (i = 0; i < MAX_HAND; i++)
	{
	    if ( i % 2 == 0 ){
			mix1[i] = copper;
		}
		if ( i % 2 != 0 ){
			mix1[i] = gold;
		}
    }
	printf("----------------- Testing updateCoins() ----------------\n\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)  //
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("TEST 1: Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Testing copper\n");
                printf("coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
                myAssert(G.coins == handCount * 1 + bonus, __FILE__, __LINE__); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Testing silver\n");
                printf("coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
                myAssert(G.coins == handCount * 2 + bonus, __FILE__, __LINE__); // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("Testing gold\n");
                printf("coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
                myAssert(G.coins == handCount * 3 + bonus, __FILE__, __LINE__); // check if the number of coins is correct
               	memcpy(G.hand[p], mix1, sizeof(int) * handCount); // set all the cards to mix1
			    updateCoins(p, &G, bonus);
				int j;
				int newHandCount = 0;
				//Get total value of mixed hand
				for (j = 0; j < handCount; j++){
					if ( G.hand[p][j] == 4 ){ // copper
						newHandCount = newHandCount + 1;
					}
					if ( G.hand[p][j] == 6 ){ // gold
						newHandCount = newHandCount + 3;

					}
				}
#if (NOISY_TEST == 1)
                printf("Testing mixed coins\n");
			    printf("G.coins = %d, expected = %d\n", G.coins, newHandCount + bonus);
#endif
			    myAssert(G.coins == newHandCount + bonus, __FILE__, __LINE__); // check if the number of coins is correct


            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
