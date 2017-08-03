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
    int i;
    int numbPlayers = 2;
    int player0 = 0;
    int player1 = 1;

    int handpos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;
    struct gameState state, stateOriginal;

    printf("Testing -> council_roomCard()\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOriginal,23,sizeof(struct gameState));

    // create the game state
    initializeGame(numbPlayers, k, seed, &state);

    // copy it to preserve it
    memcpy(&stateOriginal, &state, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("\nPlayer1 gains 4 cards\n");
    assertTrue(state.handCount[player1],stateOriginal.handCount[player1]+3);

    printf("\nPlayer1 gains 4 cards from his own pile\n");
    assertTrue(state.deckCount[player1],stateOriginal.deckCount[player1]-4);

    printf("\nPlayer1 number of buys increments\n");
    assertTrue(state.numBuys,stateOriginal.numBuys+1);

    printf("\nNo change to victory card piles\n");
    printf("Province Pile\n");
    assertTrue(state.supplyCount[province],stateOriginal.supplyCount[province]);
    printf("Duchy Pile\n");
    assertTrue(state.supplyCount[duchy],stateOriginal.supplyCount[duchy]);
    printf("Estate Pile\n");
    assertTrue(state.supplyCount[estate],stateOriginal.supplyCount[estate]);

    printf("\nNo change to kingdom card piles\n");
    for (i = 0; i < 10; i++) {
        printf("checking card piles...\n");
        assertTrue(state.supplyCount[k[i]],stateOriginal.supplyCount[k[i]]);
    }

    printf("\nPlayer0 gains a card\n");
    assertTrue(state.handCount[player0],stateOriginal.handCount[player0]+1);
    printf("\nPlayer0 gains a card from his own deck\n");
    assertTrue(state.deckCount[player0],stateOriginal.deckCount[player0]-1);

    if (failureCount) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failureCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}
