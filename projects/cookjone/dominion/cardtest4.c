#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int failureCount = 0;

void assertTrue(int a, int b) {
    if (a == b) {
        printf("Test: PASSED\n");
    }
    else {
        printf("Test: FAILED\n");
        failureCount++;
    }
}


int main () {
    int i;
    int numbPlayers = 2;
    int player0 = 0;
    int player1 = 1;

    int handpos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;
    struct gameState state, stateOriginal;

    printf("Testing -> villageCard()\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&stateOriginal,23,sizeof(struct gameState));
    initializeGame(numbPlayers, k, seed, &state);
    memcpy(&stateOriginal, &state, sizeof(struct gameState));

    cardEffect(village, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("\nPlayer0 gains 1 card\n");
    assertTrue(state.handCount[player0],stateOriginal.handCount[player0]);

    printf("\nPlayer0 gains 1 card from his own pile\n");
    assertTrue(state.deckCount[player0],stateOriginal.deckCount[player0]-1);

    printf("\nPlayer0 gains two actions\n");
    assertTrue(state.numActions,stateOriginal.numActions+2);

    printf("\nNo change to victory card piles\n");
    printf("Province Pile\n");
    assertTrue(state.supplyCount[province],stateOriginal.supplyCount[province]);
    printf("Duchy Pile\n");
    assertTrue(state.supplyCount[duchy],stateOriginal.supplyCount[duchy]);
    printf("Estate Pile\n");
    assertTrue(state.supplyCount[estate],stateOriginal.supplyCount[estate]);

    printf("\nPlayer1 was not affected\n");
    printf("Hand Count\n");
    assertTrue(state.handCount[player1],stateOriginal.handCount[player1]);
    printf("Deck Count\n");
    assertTrue(state.deckCount[player1],stateOriginal.deckCount[player1]);

    printf("\nNo change to kingdom card piles\n");
    for (i = 0; i < 10; i++) {
        printf("checking card piles...\n");
        assertTrue(state.supplyCount[k[i]],stateOriginal.supplyCount[k[i]]);
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
