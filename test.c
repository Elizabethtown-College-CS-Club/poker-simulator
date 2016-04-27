#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "evaluator.h"

int main()
{
	srand(time(NULL));

	deck_t deck;
	init_deck(&deck);

	shuffle(&deck);

	hand_t hand_a, hand_b;

	for (int i = 0; i < HAND_SIZE; ++i) {
		hand_a.cards[i] = draw(&deck);
		hand_b.cards[i] = draw(&deck);
	}

	printf("%s: %d\n", hand_names[0], LAST_ROYAL_FLUSH);
	printf("%s: %d\n", hand_names[1], LAST_STRAIGHT_FLUSH);
	printf("%s: %d\n", hand_names[2], LAST_FOUR_KIND);
	printf("%s: %d\n", hand_names[3], LAST_FULL_HOUSE);
	printf("%s: %d\n", hand_names[4], LAST_FLUSH);
	printf("%s: %d\n", hand_names[5], LAST_STRAIGHT);
	printf("%s: %d\n", hand_names[6], LAST_THREE_KIND);
	printf("%s: %d\n", hand_names[7], LAST_TWO_PAIR);
	printf("%s: %d\n", hand_names[8], LAST_ONE_PAIR);
	printf("%s: %d\n", hand_names[9], LAST_HIGH_CARD);
	
	printf("Hand A:\n");
	print_hand(&hand_a);
	printf("\nBits: ");
	print_bits(hand_bits(&hand_a));
	printf("\n");
	int rank_a = score_hand(&hand_a);
	printf("Rank: %d\n", rank_a);
	char* hand_a_name = hand_name(rank_a);
	printf("Name: %s\n", hand_a_name);

	printf("\n---------\n\n");

	printf("Hand B:\n");
	print_hand(&hand_b);
	printf("\nBits: ");
	print_bits(hand_bits(&hand_b));
	printf("\n");
	int rank_b = score_hand(&hand_b);
	printf("Rank: %d\n", rank_b);
	char* hand_b_name = hand_name(rank_b);
	printf("Name: %s\n", hand_b_name);
	
	if (rank_a < rank_b)
		printf("Hand A wins!!!!\n");
	else if (rank_b < rank_a)
		printf("Hand B wins!!!!\n");
	else
		printf("Tie!!!!");

	free(hand_a_name);
	free(hand_b_name);

	return 0;
}
