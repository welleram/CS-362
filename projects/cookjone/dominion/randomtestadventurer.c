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
int shuffleFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;
int treasureCountFails = 0;

void checkAdventurerCard(int p, struct gameState *post) {
    int PostTreasureCount = 0;
    int PreTreasureCount = 0;
    int temphand[MAX_HAND];
    int drawntreasure = 0;
    struct gameState pre;
    int cardDrawn, card;
    int bonus = 0;
    int r,s,t,i;
    int z = 0;
    memcpy(&pre,post,sizeof(struct gameState));
    r = cardEffect(adventurer,0,0,0,post,0,&bonus);
    if (r) {
        cardEffectFails++;
    }
    while(drawntreasure < 2) {
            if (pre.deckCount[p] < 1) {//if the deck is empty we need to shuffle discard and add to deck
                    s = shuffle(p, &pre);
                    if (s == -1 && pre.deckCount[p] >= 1) {
                      shuffleFails++;
                    }
            }
            t = drawCard(p, &pre);
            if (t == -1 && pre.deckCount[p] != 0) {
                drawCardFails++;
            }
            cardDrawn = pre.hand[p][pre.handCount[p] - 1];//top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                    drawntreasure++;
            else{
                    temphand[z] = cardDrawn;
                    pre.handCount[p]--; //this should just remove the top card (the most recently drawn one).
                    z++;
            }
    }
    while(z - 1 >= 0) {
            pre.discard[p][pre.discardCount[p]++] = temphand[z - 1]; // discard all cards in play that have been drawn
            z = z - 1;
    }
    for (i = 0; i < post->handCount[p]; i++) {
        card = post->hand[p][i];
        if (card == copper || card == silver || card == gold) {
            PostTreasureCount++;
        }
    }
    for (i = 0; i < pre.handCount[p]; i++) {
        card = pre.hand[p][i];
        if (card == copper || card == silver || card == gold) {
            PreTreasureCount++;
        }
    }
    if (PostTreasureCount != PreTreasureCount) {
      treasureCountFails++;
    }
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int postDCC = post->discardCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];
    int preDCC = pre.discardCount[p];
    if (!(postHC == preHC && postDC == preDC && postDCC == preDCC)) {
        deckHandCountFails++;
    }
}

int main () {
    printf("***** RANDOM TEST *****\n");
    printf("File: randomtestadventurer.c\n");
    printf("Function: adventurerCard()\n");
    printf("***********************\n");
    int iterations = 10000;
    int treasures[] = {copper,silver,gold};
    int numTreasures;
    int i, n, p;
    struct gameState G;
    int min = 3;
    srand(time(NULL));
    for (n = 0; n < iterations; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = floor(Random() * 256);
      }
      p = floor(Random() * MAX_PLAYERS);
      G.deckCount[p] = floor(Random() * ((MAX_DECK - min) + 1) + min);
      numTreasures = floor(Random() * ((G.deckCount[p] - min) + 1) + min);
      for (i = 0; i < numTreasures; i++) {
        G.deck[p][i] = treasures[rand() % 3];
      }
      G.discardCount[p] = 0;//floor(Random() * ((G.deckCount[p] - numTreasures - min) + 1) + min);
      G.handCount[p] = floor(Random() * ((MAX_HAND - min) + 1) + min);
      G.playedCardCount = floor(Random() * ((MAX_DECK - 1 - min) + 1) + min);
      G.whoseTurn = p;

      checkAdventurerCard(p, &G);
    }
    int totalFails = cardEffectFails + drawCardFails + shuffleFails +
                    deckHandCountFails + treasureCountFails;

    if (iterations - totalFails <= 0) {
      printf("\n***** RESULTS *****\n");
      printf("PASSED TESTS: %d\n",0);
      printf("FAILED TESTS: %d\n",iterations);
    }
    else {
      printf("\n***** RESULTS *****\n");
      printf("PASSED TESTS: %d\n",iterations - totalFails);
      printf("FAILED TESTS: %d\n",totalFails);
    }

    if (totalFails == 0) {
        printf ("***** PASSED RANDOM TEST *****\n\n");
    }
    else {
        printf("\n***** FAILURE REPORT *****\n");
        printf("shuffle() failed: %d\n",shuffleFails);
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("Treasure Count mismatch: %d\n",treasureCountFails);
        printf("Hand/Deck Count mismatch: %d\n",deckHandCountFails);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf ("****** COVERAGE ******\n");
    return 0;
}
