// User program should seed rand() before running shuffle

#include "deck.h"

#include <stdio.h>
#include <stdlib.h>

const char const * VALUE_NAMES[] = { NULL, "Ace", "2", "3", "4", "5", "6", "7", "8", "9",
			"10", "Jack", "Queen", "King" };
const char const * SUIT_NAMES[] = { NULL, "Hearts", "Diamonds", "Spades", "Clubs" };

/* Initializes card to (0, 0) if parameters are invalid */
card_t init_card(char value, char suit)
{
	card_t card;

	if (value >= 0 && value <= 13)
		card.value = value;
	else
		card.value = 0;

	if (suit >= 0 && suit <= 4)
		card.suit = suit;
	else
		card.suit = 0;

	return card;
}

void init_deck(deck_t* deck)
{
	int count = 0;

	for (char suit = 1; suit <= 4; ++suit) {
		for (char value = 1; value <= 13; ++value) {
			deck->cards[count] = init_card(value, suit);
			count++;
		}
	}

	deck->size = DECK_SIZE;
	deck->next = 0;
}

void shuffle(deck_t* deck)
{
	// Fisher-Yates shuffle algorithm
	for (int i = 0; i < deck->size - 1; ++i) {
		int j = rand() % (deck->size - i);

		// Perform swap
		card_t temp = deck->cards[i];
		deck->cards[i] = deck->cards[i + j];
		deck->cards[i + j] = temp;
	}
} 

/* Draws a card from the deck. Returns a joker if deck is empty */
card_t draw(deck_t* deck)
{
	if (deck->next >= DECK_SIZE)
		return init_card(0, 0);
	else
		return deck->cards[deck->next++];
}

void print_card(card_t card)
{
	printf("%s of %s", VALUE_NAMES[card.value], SUIT_NAMES[card.suit]);
}

void print_deck(deck_t* deck)
{
	for (int i = 0; i < deck->size; ++i) {
		printf("%d: \"", i + 1);
		print_card(deck->cards[i]);
		printf("\"\n");
	}
}
