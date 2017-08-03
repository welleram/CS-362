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
    int treasureCount = 0;
    int treasureCountOriginal = 0;
    int numbPlayers = 2;
    int player0 = 0;
    int player1 = 1;
    int card;
    int handpos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;

    // game states
    struct gameState state, stateOriginal;

    printf("Testing -> adventurerCard()\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOriginal,23,sizeof(struct gameState));

    // create a state
    initializeGame(numbPlayers, k, seed, &state);

    // copy it to preserve it
    memcpy(&stateOriginal, &state, sizeof(struct gameState));

    cardEffect(adventurer, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("\nPlayer0 gains 2 cards\n");
    assertTrue(state.handCount[player0],stateOriginal.handCount[player0]+2);

    // checks how much treasure is gained
    for (i = 0; i < state.handCount[player0]; i++) {
        card = state.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            treasureCount++;
        }
    }

    // checks default treasure count
    for (i = 0; i < stateOriginal.handCount[player0]; i++) {
        card = stateOriginal.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            treasureCountOriginal++;
        }
    }

    printf("\nPlayer0 gains 2 treasure cards\n");
    assertTrue(treasureCountOriginal+2,treasureCount);

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

    printf("\nPlayer1 was not affected\n");
    printf("Hand Count\n");
    assertTrue(state.handCount[player1],stateOriginal.handCount[player1]);
    printf("Deck Count\n");
    assertTrue(state.deckCount[player1],stateOriginal.deckCount[player1]);

    if (failureCount) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failureCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}
