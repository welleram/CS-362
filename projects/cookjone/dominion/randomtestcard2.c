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
int numBuysFails = 0;
int otherPlayerDeckHandFails = 0;

// function to check the council_roomCard
void checkCouncil_RoomCard(int p, struct gameState *post) {
    int r,s,t,u,v,w,x,i;
    int bonus = 0;

    // game state variable to manually act on the functions actions
    struct gameState pre;

    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));

    // call the card effect function with the smithy card
    r = cardEffect(council_room,0,0,0,post,0,&bonus);

    // call draw card 4 times
    s = drawCard(p,&pre);
    t = drawCard(p,&pre);
    u = drawCard(p,&pre);
    v = drawCard(p,&pre);

    pre.numBuys++;

    // have each other player draw a card
    for (i = 0; i < pre.numPlayers; i++) {
        if (i != p) {
            w = drawCard(i,&pre);
            // check if drawcard failed
            if (w == -1 && pre.deckCount[i] != 0) {
                drawCardFails++;
            }
        }
    }

    // call discardCard
    x = discardCard(0, p, &pre, 0);

    // get values of hand and deck counts
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];

    // check if numBuys dont match
    if (pre.numBuys != post->numBuys) {
        numBuysFails++;
    }

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
    if (v == -1 && pre.deckCount[p] != 0) {
        drawCardFails++;
    }

    // check if cardeffect or discardCard failed
    if (!(r == 0 && x == 0)) {
        if (r) {
            cardEffectFails++;
        }
        if (x) {
            discardCardFails++;
        }
    }

    // check if the hand and deck counts dont match up
    if (!(postHC == preHC && postDC == preDC)) {
        deckHandCountFails++;
    }

    // check if the other players hand and deck counts match
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

    // randomly initialized the game state
    for (n = 0; n < iterations; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // randomly select appropriate values
        G.numPlayers = numberOfPlayers[rand() % 3];
        G.numBuys = 1;
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        player = G.numPlayers - 2;
        deckCount = floor(Random() * MAX_DECK);
        handCount = floor(Random() * MAX_HAND);
        discardCount = floor(Random() * MAX_DECK);
        G.whoseTurn = player;
        // set hand and deck values of other players
        for (i = 0; i < G.numPlayers; i++) {
            G.deckCount[i] = deckCount;
            G.handCount[i] = handCount;
            G.discardCount[i] = discardCount;
        }
        // call the check function
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
