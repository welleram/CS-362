#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// fail counter variables
int cardEffectFails = 0;
int discardCardFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;

// function to check the smithyCard
void checkSmithyCard(int p, struct gameState *post) {
    int r,s,t,u,v;

    // game state variable to manually act on the functions actions
    struct gameState pre;

    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));
    int bonus = 0;

    // call the card effect function with the smithy card
    r = cardEffect(smithy,0,0,0,post,0,&bonus);

    // call draw card 3 times
    s = drawCard(p,&pre);
    t = drawCard(p,&pre);
    u = drawCard(p,&pre);

    // call discardCard
    v = discardCard(0, p, &pre, 0);

    // get values of hand and deck counts
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];

    // check if any drawcard failed
    if (s == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (t == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (u == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }

    // check if cardeffect or discardCard failed
    if (!(r == 0 && v == 0)) {
        if (r) {
            cardEffectFails++;
        }
        if (v) {
            discardCardFails++;
        }
    }

    // check if the hand and deck counts dont match up
    if (!(postHC == preHC && postDC == preDC)) {
        deckHandCountFails++;
    }
}

int main () {
    printf("***** RANDOM TEST *****\n");
    printf("File: randomcardtest1.c\n");
    printf("Function: simthyCard()\n");
    printf("***********************\n");

    int iterations = 10000;
    int i, n, player;
    struct gameState G;
    srand(time(NULL));

    // randomly initialized the game state
    for (n = 0; n < iterations; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // randomly select appropriate values
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playerlayedCardCount = floor(Random() * (MAX_DECK-1));
        G.whoseTurn = player;
        // call the check function
        checkSmithyCard(player,&G);
    }
    int totalFails = cardEffectFails + discardCardFails +
                        drawCardFails + deckHandCountFails;
    printf("\n***** RESULTS *****\n");
    printf("PASSED TESTS: %d\n",iterations - totalFails);
    printf("FAILED TESTS: %d\n",totalFails);

    if (totalFails == 0) {
        printf ("***** PASSED RANDOM TEST *****\n\n");
    }
    else {
        printf("\n***** FAILURE REPORT *****\n");
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("discardCard() failed: %d\n",discardCardFails);
        printf("Hand/Deck Count mismatch: %d\n",deckHandCountFails);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf ("****** COVERAGE ******\n");
    return 0;
}
