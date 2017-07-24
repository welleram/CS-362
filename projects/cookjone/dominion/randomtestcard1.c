#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int cardEffectFails = 0;
int discardCardFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;

void checkSmithyCard(int p, struct gameState *post) {
    int r,s,t,u,v;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    int bonus = 0;
    r = cardEffect(smithy,0,0,0,post,0,&bonus);
    s = drawCard(p,&pre);
    t = drawCard(p,&pre);
    u = drawCard(p,&pre);
    v = discardCard(0, p, &pre, 0);
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];
    if (s == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (t == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (u == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (!(r == 0 && v == 0)) {
        if (r) {
            cardEffectFails++;
        }
        if (v) {
            discardCardFails++;
        }
    }
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
    int i, n, p;
    struct gameState G;
    srand(time(NULL));

    for (n = 0; n < iterations; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        G.whoseTurn = p;
        checkSmithyCard(p,&G);
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
