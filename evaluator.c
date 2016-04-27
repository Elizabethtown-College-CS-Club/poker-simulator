#include "evaluator.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

const char* hand_names[] = { "Royal Flush", "Straight Flush", "Four of a Kind",
	"Full House", "Flush", "Straight", "Three of a Kind", "Two Pair",
	"One Pair", "High Card" };

int score_hand(hand_t* hand)
{
	int bits = hand_bits(hand);

	// Part 1 - Same suit
	if (same_suit(hand))
		return flushes[bits];

	// Part 2 - Unique 5 (not flush)
	if (unique5[bits] > 0)
		return unique5[bits];

	// Part 3 - Non-unique (products of primes)
	int hand_product = 1;

	for (int i = 0; i < HAND_SIZE; ++i)
		hand_product *= primes[convert_card_value(hand->cards[i]) - 1];

	size_t high = PRODUCT_COUNT;
	size_t low = 0;

	while (low < high) {
		size_t pos = (low + high) / 2;

		if (hand_product < products[pos])
			high = pos;
		else if (hand_product > products[pos])
			low = pos + 1;
		else
			return values[pos];
	}

	// BAD
	return -1;
}

int hand_bits(hand_t* hand)
{
	int bits = 0;

	for (int i = 0; i < HAND_SIZE; ++i) {
		// Convert from A234...JQK to 234...QKA system
		char value = convert_card_value(hand->cards[i]);

		bits |= 1 << (value - 1);
	}

	return bits;
}

bool same_suit(hand_t* hand)
{
	char first_suit = hand->cards[0].suit;

	// Look for mismatched suits
	for (int i = 1; i < HAND_SIZE; ++i)
		if (hand->cards[i].suit != first_suit)
			return false;

	// All must have same suit
	return true;
}

/* Convert from A234...JQK to 234...QKA system */
char convert_card_value(card_t card)
{
	return (card.value > 1) ? (card.value - 1) : (13);
}

void print_hand(hand_t* hand)
{
	printf("{ ");
	for (int i = 0; i < HAND_SIZE; ++i) {
		if (i != 0)
			printf(", ");

		printf("(");
		print_card(hand->cards[i]);
		printf(")");
	}
	printf(" }");
}

void print_bits(int value)
{
	for (int i = sizeof(int) * 8 - 1; i >= 0; --i)
		printf("%d", (value >> i) & 1);
}

char* hand_name(int rank)
{
	if (rank == LAST_ROYAL_FLUSH)
		return dupe_string(hand_names[0]);
	else if (rank <= LAST_STRAIGHT_FLUSH)
		return dupe_string(hand_names[1]);
	else if (rank <= LAST_FOUR_KIND)
		return dupe_string(hand_names[2]);
	else if (rank <= LAST_FULL_HOUSE)
		return dupe_string(hand_names[3]);
	else if (rank <= LAST_FLUSH)
		return dupe_string(hand_names[4]);
	else if (rank <= LAST_STRAIGHT)
		return dupe_string(hand_names[5]);
	else if (rank <= LAST_THREE_KIND)
		return dupe_string(hand_names[6]);
	else if (rank <= LAST_TWO_PAIR)
		return dupe_string(hand_names[7]);
	else if (rank <= LAST_ONE_PAIR)
		return dupe_string(hand_names[8]);
	else // (rank <= LAST_HIGH_CARD)
		return dupe_string(hand_names[9]);
}

char* dupe_string(const char* string)
{
	size_t length = strlen(string) + 1;
	char* new_string = (char*) malloc(length * sizeof(char));

	for (size_t i = 0; i < length; ++i)
		new_string[i] = string[i];

	return new_string;
}
