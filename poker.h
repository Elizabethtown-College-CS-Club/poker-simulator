#ifndef POKER_H
#define POKER_H

#include "deck.h"
#include "evaluator.h"

typedef enum { HAS_NOT_ACTED, HAS_ACTED, FOLDED, ALL_IN } state_t;

typedef struct {
	char* name;
	card_t cards[2];
	int funds;
	int cur_bet;
	state_t state;
} player_t;

typedef struct pot {
	int participants; // Bitmask - a 1 at bit N means player N is involved
	int total;
	int bet_to_match;
	struct pot* next;
} pot_t;

void deal_in(player_t*, deck_t*);
int get_rank(player_t*, card_t[]);
void init_pot(pot_t*, bool);
void set_participant(pot_t*, int, bool);
void reset(player_t*);
void init_player(player_t*, const char*, int);
void free_player(player_t*);
void read_line(char*, size_t);

#endif
