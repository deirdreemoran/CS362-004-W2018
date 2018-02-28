//unittest3.c
// Name: Deirdre Moran
// Function:  Tests the getCost() function

/*
 * Include the following lines in your make__FILE__:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 unittest1.c -g dominion.o rngs.o $(CFLAGS)
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
    int i;
    int cost;
    int card;
    int allCards[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer
    				, council_room, feast, gardens, mine, remodel, smithy, village
    				, baron, great_hall, minion, steward, tribute, ambassador, cutpurse
    				, embargo, outpost, salvager, sea_hag, treasure_map };
	printf("----------------- Testing getCost() ----------------\n\n");
    for(card = 0; card < 27; card++)
	{
			i = allCards[card];
			cost = getCost(i);

			if (i == 0) // CURSE card
			{
#if (NOISY_TEST == 1)
				printf("CURSE:  Cost is %d, expected is %d.\n", cost, 0);
#endif
				myAssert(cost == 0, __FILE__, __LINE__);
			}

			if (i == 1) // ESTATE card
			{
#if (NOISY_TEST == 1)
				printf("ESTATE:  Cost is %d, expected is %d.\n", cost, 2);
#endif
				myAssert(cost == 2, __FILE__, __LINE__);
			}

			if (i == 2) // DUCHY card
			{
#if (NOISY_TEST == 1)
				printf("DUCHY:  Cost is %d, expected is %d.\n", cost, 5);
#endif
				myAssert(cost == 5, __FILE__, __LINE__);
			}


			if (i == 3) // PROVINCE card
			{
#if (NOISY_TEST == 1)
				printf("PROVINCE:  Cost is %d, expected is %d.\n", cost, 8);
#endif
				myAssert(cost == 8, __FILE__, __LINE__);
			}

			if (i == 4) // COPPER card
			{
#if (NOISY_TEST == 1)
				printf("COPPER:  Cost is %d, expected is %d.\n", cost, 0);
#endif
				myAssert(cost == 0, __FILE__, __LINE__);
			}

			if (i == 5) // SILVER card
			{
#if (NOISY_TEST == 1)
				printf("SILVER:  Cost is %d, expected is %d.\n", cost, 3);
#endif
				myAssert(cost == 3, __FILE__, __LINE__);
			}

			if (i == 6) // GOLD card
			{
#if (NOISY_TEST == 1)
				printf("GOLD:  Cost is %d, expected is %d.\n", cost, 6);
#endif
				myAssert(cost == 6, __FILE__, __LINE__);
			}

			if (i == 7) // ADVENTURER card
			{
#if (NOISY_TEST == 1)
				printf("ADVENTURER:  Cost is %d, expected is %d.\n", cost, 6);
#endif
				myAssert(cost == 6, __FILE__, __LINE__);
			}

			if (i == 8) // COUNCIL_ROOM card
			{
#if (NOISY_TEST == 1)
				printf("COUNCIL_ROOM:  Cost is %d, expected is %d.\n", cost, 5);
#endif
				myAssert(cost == 5, __FILE__, __LINE__);
			}

			if (i == 9) // FEAST card
			{
#if (NOISY_TEST == 1)
				printf("FEAST:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 10) // GARDENS card
			{
#if (NOISY_TEST == 1)
				printf("GARDENS:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 11) // MINE card
			{
#if (NOISY_TEST == 1)
				printf("MINE:  Cost is %d, expected is %d.\n", cost, 5);
#endif
				myAssert(cost == 5, __FILE__, __LINE__);
			}

			if (i == 12) // REMODEL card
			{
#if (NOISY_TEST == 1)
				printf("REMODEL:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 13) // SMITHY card
			{
#if (NOISY_TEST == 1)
				printf("SMITHY:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}
			if (i == 14) // VILLAGE card
			{
#if (NOISY_TEST == 1)
				printf("VILLAGE:  Cost is %d, expected is %d.\n", cost, 3);
#endif
				myAssert(cost == 3, __FILE__, __LINE__);
			}

			if (i == 15) // BARON card
			{
#if (NOISY_TEST == 1)
				printf("BARON:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 16) // GREAT_HALL card
 			{
#if (NOISY_TEST == 1)
				printf("GREAT_HALL:  Cost is %d, expected is %d.\n", cost, 3);
#endif
				myAssert(cost == 3, __FILE__, __LINE__);
			}

			if (i == 17) // MINION card
			{
#if (NOISY_TEST == 1)
				printf("MINION:  GREAT_HALL:  Cost is %d, expected is %d.\n", cost, 5);
#endif
				myAssert(cost == 5, __FILE__, __LINE__);
			}

			if (i == 18) // STEWARD card
			{
#if (NOISY_TEST == 1)
				printf("STEWARD:  Cost is %d, expected is %d.\n", cost, 3);
#endif
				myAssert(cost == 3, __FILE__, __LINE__);
			}

			if (i == 19) // TRIBUTE card
			{
#if (NOISY_TEST == 1)
				printf("TRIBUTE:  Cost is %d, expected is %d.\n", cost, 5);
#endif
				myAssert(cost == 5, __FILE__, __LINE__);
			}

			if (i == 20) // AMBASSADOR card
			{
#if (NOISY_TEST == 1)
				printf("AMBASSADOR:  Cost is %d, expected is %d.\n", cost, 3);
#endif
				myAssert(cost == 3, __FILE__, __LINE__);
			}

			if (i == 21) // CUTPURSE card
			{
#if (NOISY_TEST == 1)
				printf("CUTPURSE:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 22) // EMBARGO card
			{
#if (NOISY_TEST == 1)
				printf("EMBARGO:  Cost is %d, expected is %d.\n", cost, 2);
#endif
				myAssert(cost == 2, __FILE__, __LINE__);
			}


			if (i == 23) // OUTPOST card
			{
#if (NOISY_TEST == 1)
				printf("OUTPOST:  Cost is %d, expected is %d.\n", cost, 5);
#endif
				myAssert(cost == 5, __FILE__, __LINE__);
			}

			if (i == 24) // SALVAGER card
			{
#if (NOISY_TEST == 1)
				printf("SALVAGER:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 25) // SEA_HAG card
			{
#if (NOISY_TEST == 1)
				printf("SEA_HAG:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}

			if (i == 26) // TREASURE_MAP card
			{
#if (NOISY_TEST == 1)
				printf("TREASURE_MAP:  Cost is %d, expected is %d.\n", cost, 4);
#endif
				myAssert(cost == 4, __FILE__, __LINE__);
			}
		}


	printf("All tests passed!\n");
	return 0;
}
