#ifndef DECK_H
#define DECK_H

#include <stddef.h>

#define DECK_SIZE 52

typedef struct 
{
	char value; // 1-13 representing (A, 2-9, J, Q, K)
	char suit; // 1-4 representing Hearts, Diamonds, Spades, Clubs
} card_t;

typedef struct
{
	card_t cards[DECK_SIZE];
	size_t size;
	size_t next; // Next card to be drawn
} deck_t;

card_t init_card(char, char);
void init_deck(deck_t*);

void shuffle(deck_t*);
card_t draw(deck_t*);

void print_card(card_t);
void print_deck(deck_t*);

#endif
