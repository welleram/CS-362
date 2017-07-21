#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int checkSmithyCard(int currentPlayer, int handPos, struct gameState *testState) {
    struct gameState manualState;
    memcpy (&manualState, testState, sizeof(struct gameState));
    int r = smithyCard(currentPlayer, handPos, testState);
    drawCard(currentPlayer, manualState);
    drawCard(currentPlayer, manualState);
    drawCard(currentPlayer, manualState);
    discardCard(handPos, currentPlayer, manualState, 0);


    if (pre.deckCount[p] > 0) {
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
    pre.deckCount[p]--;
    } else if (pre.discardCount[p] > 0) {
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
    memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    pre.handCount[p]++;
    pre.deckCount[p] = pre.discardCount[p]-1;
    pre.discardCount[p] = 0;
    }

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {
    int i, n, r, p, deckCount, discardCount, handCount;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf ("Testing drawCard.\n");

    printf ("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkDrawCard(p, &G);
    }

    printf ("ALL TESTS OK\n");

    return 0;
}
