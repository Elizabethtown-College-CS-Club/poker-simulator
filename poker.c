#include "poker.h"

#include "arrays.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER_LEN 100
#define NUM_PLAYERS 2

int main()
{
        srand(time(NULL));
	char buffer[BUFFER_LEN];
	player_t players[NUM_PLAYERS];

	printf("Enter player 1's name: ");
	read_line(buffer, BUFFER_LEN);
	init_player(&players[0], buffer, 1000);

	printf("Enter player 2's name: ");
	read_line(buffer, BUFFER_LEN);
	init_player(&players[1], buffer, 1000);

	printf("Player 1's name: %s\n", players[0].name);
	printf("Player 2's name: %s\n", players[1].name);

	// Start game

	deck_t deck;
	init_deck(&deck);
	shuffle(&deck);

	deal_in(&players[0], &deck);
	deal_in(&players[1], &deck);

	printf("%s's hand: {", players[0].name);
	print_card(players[0].cards[0]);
	printf("}, {");
	print_card(players[0].cards[1]);
	printf("}\n");
	
	printf("%s's hand: {", players[1].name);
	print_card(players[1].cards[0]);
	printf("}, {");
	print_card(players[1].cards[1]);
	printf("}\n");

	card_t community[5];

	community[0] = draw(&deck);
	community[1] = draw(&deck);
	community[2] = draw(&deck);
	community[3] = draw(&deck);
	community[4] = draw(&deck);

	printf("{");
	print_card(community[0]);
	printf("}, {");
	print_card(community[1]);
	printf("}, {");
	print_card(community[2]);
	printf("}, {");
	print_card(community[3]);
	printf("}, {");
	print_card(community[4]);
	printf("}\n");

	int player1_rank = get_rank(&players[0], community);
	int player2_rank = get_rank(&players[1], community);

	printf("%s has a hand of rank %d\n", players[0].name, player1_rank);
	printf("%s has a hand of rank %d\n", players[1].name, player2_rank);

	char* player1_hand_name = hand_name(player1_rank);
	char* player2_hand_name = hand_name(player2_rank);
	printf("%s has a %s!\n", players[0].name, player1_hand_name);
	printf("%s has a %s!\n", players[1].name, player2_hand_name);
	free(player1_hand_name);
	free(player2_hand_name);

	return 0;
}

int get_rank(player_t* player, card_t community[])
{
	// Card pool for convenience
	card_t pool[7];
	for (int i = 0; i < 2; ++i)
		pool[i] = player->cards[i];
	for (int i = 2; i < 7; ++i)
		pool[i] = community[i - 2];

	// Start at highest possible rank
	int lowest_rank = LAST_HIGH_CARD;

	// Try each combination to find the lowest rank
	for (int i = 0; i < 21; ++i) {
		// Get the hand of 5 corresponding to the given combination
		hand_t hand;
		for (int j = 0; j < 5; ++j)
			hand.cards[j] = pool[perm7[i][j]];

		int rank = score_hand(&hand);
		if (rank < lowest_rank)
			lowest_rank = rank;
	}

	return lowest_rank;
}

/*
void betting_round(player_t players[], pot_t* pot, int num_players, int start_idx)
{
	int fold_count = 0;

	// Reset bet amount and state for all players
	for (int i = 0; i < num_players; ++i) {
		players[i].cur_bet = 0;
		if (players[i].state != FOLDED)
			players[i].state = HAS_NOT_ACTED;
		else
			fold_count++;
	}

	int bet_to_match = 0;
	int i = start_idx;

	// Go until everyone has bet or folded & everyone is in for the same amount
	while ((players[i].state != HAS_ACTED || player[i].cur_bet != bet_to_match)
			&& fold_count < (num_players - 1)) {

		// Skip people who have folded
		if (players[i].state != FOLDED) {
			printf("What do you want to do, %s?\n", players[i].name);
			
			// Whether the player can bet or raise
			bool bet = (bet-to-match == 0);
	
			// Whether the player can check or call
			bool check = (players[i].cur_bet == bet_to_match);

			printf("1 - ");
			if (bet)
				printf("Bet\n");
			else
				printf("Raise\n");

			printf("2 - ");
			if (bet)
				printf("Check\n");
			else
				printf("Call\n");

			printf("3 - Fold\n");

			int choice;
			scanf("%d", &choice);

			if (choice == 1) {
				printf("How much?: ");
			} else if (choice == 2) {
				if (call)
			} else {
				player[i].state = FOLDED;
				fold_count++;
			}
		}

		i = (i + 1) % num_players;
	}
}
*/

void deal_in(player_t* player, deck_t* deck)
{
	player->cards[0] = draw(deck);
	player->cards[1] = draw(deck);

	reset(player);
}

void init_pot(pot_t* pot, bool all_ones)
{
	pot->participants = all_ones ? ~0 : 0;
	pot->total = 0;
	pot->bet_to_match = 0;
	pot->next = NULL;
}

/* "adding" sets the relevant bit to 1 if true; to 0 if false. */
void set_participant(pot_t* pot, int index, bool adding)
{
	if (adding)
		pot->participants |= (1 << index);
	else
		pot->participants &= ~(1 << index);
}

void reset(player_t* player)
{
	player->cur_bet = 0;
	player->state = HAS_NOT_ACTED;
}

void init_player(player_t* player, const char* name, int funds)
{
	player->name = dupe_string(name);
	player->funds = funds;

	player->cards[0] = init_card(0, 0);
	player->cards[1] = init_card(0, 0);

	reset(player);
}

void free_player(player_t* player)
{
	free(player->name);
}

void read_line(char* str, size_t size)
{
	size_t i = 0;
	int current = getchar();
	while (i < (size - 1) && current != EOF && current != '\n') {
		str[i] = (char) current;
		current = getchar();
		i++;
	} 

	// Flush remaining characters in line
	while (current != EOF && current != '\n')
		current = getchar();

	str[i] = '\0';
}
