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
int numBuysFails = 0;
int otherPlayerDeckHandFails = 0;

void checkCouncil_RoomCard(int p, struct gameState *post) {
    int r,s,t,u,v,w,x,i;
    int bonus = 0;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    r = cardEffect(council_room,0,0,0,post,0,&bonus);
    s = drawCard(p,&pre);
    t = drawCard(p,&pre);
    u = drawCard(p,&pre);
    v = drawCard(p,&pre);
    pre.numBuys++;
    for (i = 0; i < pre.numPlayers; i++) {
        if (i != p) {
            w = drawCard(i,&pre);
            if (w == -1 && pre.deckCount[i] != 0) {
                drawCardFails++;
            }
        }
    }
    x = discardCard(0, p, &pre, 0);
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];
    if (pre.numBuys != post->numBuys) {
        numBuysFails++;
    }
    if (s == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (t == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (u == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (v == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }
    if (!(r == 0 && x == 0)) {
        if (r) {
            cardEffectFails++;
        }
        if (x) {
            discardCardFails++;
        }
    }
    if (!(postHC == preHC && postDC == preDC)) {
        deckHandCountFails++;
    }
    for (i = 0; i < pre.numPlayers; i++) {
        if (i != p) {
            if (!(post->handCount[i] == pre.handCount[i] &&
                  post->deckCount[i] == pre.deckCount[i])) {
                      otherPlayerDeckHandFails++;
            }
        }
    }
}

int main () {
    printf("***** RANDOM TEST *****\n");
    printf("File: randomcardtest2.c\n");
    printf("Function: council_roomCard()\n");
    printf("***********************\n");

    int iterations = 10000;
    int i, n, player, deckCount, handCount, discardCount;
    int numberOfPlayers[] = {2,3,4};
    struct gameState G;
    srand(time(NULL));

    for (n = 0; n < iterations; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        G.numPlayers = numberOfPlayers[rand() % 3];
        G.numBuys = 1;
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        player = G.numPlayers - 2;
        if (player >=   G.numPlayers) {
          printf("ERROR\n");
        }
        deckCount = floor(Random() * MAX_DECK);
        handCount = floor(Random() * MAX_HAND);
        discardCount = floor(Random() * MAX_DECK);
        G.whoseTurn = player;
        for (i = 0; i < G.numPlayers; i++) {
            G.deckCount[i] = deckCount;
            G.handCount[i] = handCount;
            G.discardCount[i] = discardCount;
        }
        checkCouncil_RoomCard(player,&G);
    }
    int totalFails = cardEffectFails + discardCardFails + drawCardFails
                    + deckHandCountFails + numBuysFails;
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
        printf("numBuys Count mismatch: %d\n",numBuysFails);
        printf("Other players hand/deck count mismatch: %d\n",otherPlayerDeckHandFails);
        printf("Selected player hand/deck count mismatch: %d\n",deckHandCountFails);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf ("****** COVERAGE ******\n");
    return 0;
}
