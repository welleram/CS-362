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
    int numbPlayers = 2;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;

    printf("Testing -> isGameOver()\n");

    memset(&state,23,sizeof(struct gameState));
    initializeGame(numbPlayers, k, seed, &state);

    state.supplyCount[province] = 0;

    printf("\nProvince cards empty\n");
    assertTrue(isGameOver(&state),1);

    state.supplyCount[province] = 1;

    state.supplyCount[0] = 0;
    state.supplyCount[1] = 0;
    state.supplyCount[2] = 0;

    printf("\nThree supply piles empty\n");
    assertTrue(isGameOver(&state),1);

    state.supplyCount[0] = 1;
    state.supplyCount[1] = 1;
    state.supplyCount[2] = 1;

    printf("\nProvince cards not empty\n");
    printf("\nThree supply piles not empty\n");
    assertTrue(isGameOver(&state),0);

    if (failureCount) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failureCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}
