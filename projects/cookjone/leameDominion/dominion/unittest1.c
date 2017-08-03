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
    int i, b;
    int numbPlayers = 2;
    int player = 0;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;
    int handCount;
    int bonus = 1;

    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    // arrays full of designated treasure
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf("Testing -> updateCoins()");

    // test how updateCoins handles each treasure and a different bonus and hand count
    for (handCount = 0; handCount <= 5; handCount = handCount + 5) {
        printf("\n\nTreasure cards: %d\n",handCount);
        printf("Bonus: %d\n", bonus);

        memset(&state,23,sizeof(struct gameState));
        b = initializeGame(numbPlayers, k, seed, &state);
        state.handCount[player] = handCount;

        // fill hand with all coppers
        memcpy(state.hand[player],coppers,sizeof(int)*handCount);
        updateCoins(player,&state,bonus);

        printf("\nCoin Count - copper\n");
        printf("Actual: %d\n",state.coins);
        printf("Expected: %d\n",handCount*1+bonus);

        assertTrue(state.coins,handCount*1+bonus);

        // fill hand with all silvers
        memcpy(state.hand[player],silvers,sizeof(int)*handCount);
        updateCoins(player,&state,bonus);

        printf("\nCoin Count - silver\n");
        printf("Actual: %d\n",state.coins);
        printf("Expected: %d\n",handCount*2+bonus);

        assertTrue(state.coins,handCount*2+bonus);

        // fill hand with all golds
        memcpy(state.hand[player],golds,sizeof(int)*handCount);
        updateCoins(player,&state,bonus);

        printf("\nCoin Count - gold\n");
        printf("Actual: %d\n",state.coins);
        printf("Expected: %d\n",handCount*3+bonus);

        assertTrue(state.coins,handCount*3+bonus);

        bonus = bonus + 2;
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
