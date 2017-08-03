#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// global count of test failures
int failureCount = 0;

// function to check if two ints are equal or not
void assertTrue(int a, int b) {
    if (a == b) {
        printf("Test: PASSED\n");
    }
    else {
        printf("Test: FAILED\n");
        failureCount++;
    }
}

// runs the tests
int main () {
    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;

    printf("Testing -> gainCard()\n");
    memset(&state,23,sizeof(struct gameState));
    initializeGame(2, k, seed, &state);

    printf("\nGold supply pile is empty\n");
    state.supplyCount[gold] = 0;
    assertTrue(gainCard(gold,&state,0,0),-1);
    state.supplyCount[gold] = 30;

    printf("\nAdd card to deck\n");
    int deckCount = state.deckCount[0];
    gainCard(gold,&state,1,0);
    assertTrue(deckCount+1,state.deckCount[0]);

    printf("\nAdd card to hand\n");
    int handCount = state.handCount[0];
    gainCard(gold,&state,2,0);
    assertTrue(handCount+1,state.handCount[0]);

    printf("\nAdd card to discard pile\n");
    int discardCount = state.discardCount[0];
    gainCard(gold,&state,0,0);
    assertTrue(discardCount+1,state.discardCount[0]);

    printf("\nDecrease gold supply\n");
    int goldSupply = state.supplyCount[gold];
    gainCard(gold,&state,0,0);
    assertTrue(goldSupply-1,state.supplyCount[gold]);

    if (failureCount) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failureCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}
