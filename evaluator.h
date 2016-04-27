#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <stdbool.h>
#include "deck.h"

#define PRODUCT_COUNT 4888
#define HAND_SIZE 5

// Highest ranks for a given hand type
#define LAST_ROYAL_FLUSH 1
#define LAST_STRAIGHT_FLUSH 10
#define LAST_FOUR_KIND (LAST_STRAIGHT_FLUSH + 156)
#define LAST_FULL_HOUSE (LAST_FOUR_KIND + 156)
#define LAST_FLUSH (LAST_FULL_HOUSE + 1277)
#define LAST_STRAIGHT (LAST_FLUSH + 10)
#define LAST_THREE_KIND (LAST_STRAIGHT + 858)
#define LAST_TWO_PAIR (LAST_THREE_KIND + 858)
#define LAST_ONE_PAIR (LAST_TWO_PAIR + 2860)
#define LAST_HIGH_CARD (LAST_ONE_PAIR + 1277)

typedef struct
{
	card_t cards[HAND_SIZE];
} hand_t;

extern const char* hand_names[];

int score_hand(hand_t*);
int hand_bits(hand_t*);
bool same_suit(hand_t*);
char convert_card_value(card_t);
void print_hand(hand_t*);
void print_bits(int);
char* hand_name(int);
char* dupe_string(const char*);

#endif
