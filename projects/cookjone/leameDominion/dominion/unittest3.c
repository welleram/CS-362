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
    int player = 0;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;

    printf("Testing -> shuffle()\n");
    memset(&state,23,sizeof(struct gameState));
    initializeGame(numbPlayers, k, seed, &state);

    state.deckCount[player] = 0;
    printf("\nPlayer deck count is 0\n");
    assertTrue(shuffle(player,&state),-1);

    printf("\nPlayer deck count is 10 before and after shuffle\n");
    state.deckCount[player] = 10;
    shuffle(player,&state);
    assertTrue(state.deckCount[player],10);

    printf("\nCards are shuffled\n");
    int pre_shuffle_card = state.deck[player][0];
    shuffle(player,&state);
    int post_shuffle_card = state.deck[player][0];
    if (pre_shuffle_card != post_shuffle_card) {
        assertTrue(1,1);
    }
    else {
        assertTrue(0,1);
    }

    if (failureCount) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failureCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}
