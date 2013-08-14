/*
 * $Id: turtles.c,v 1.11 2013/08/14 22:12:35 urs Exp $
 *
 * Solve the turtle game.
 */

#include <stdio.h>

static void place_card(int idx);
static int  check(int idx);
static int  mark(int idx, int dir);
static void print(int idx, int brk_flag);

typedef struct {
	int mark[4];
} CARD;

enum { RIGHT, UP, LEFT, DOWN };

static const CARD card[9] = {
	{ { -1, -2, +3, +4 } },
	{ { -1, -2, +3, +4 } },
	{ { -1, -4, +3, +4 } },
	{ { -1, -4, +3, +2 } },
	{ { -3, -1, +2, +4 } },
	{ { -3, -2, +1, +2 } },
	{ { -2, -3, +1, +4 } },
	{ { -1, -3, +4, +2 } },
	{ { -3, -4, +1, +2 } },
};

static struct {
	int no, rot;
} field[9];
static int used[9];

static int debug = 0;

int main(int argc, char **argv)
{
	if (argc > 1)
		debug = 1;

	place_card(0);

	return 0;
}

static void place_card(int idx)
{
	int no, rot;

	for (no = 0; no < 9; no++) {

		/* Eliminate duplicate solutions by requiring the whole
		 * field to be rotated such that the lowest-numbered card
		 * of the 4 corners is located in the upper left corner.
		 */
		if ((idx == 2 || idx == 6 || idx == 8) && no < field[0].no)
			continue;

		if (used[no])
			continue;
		used[no] = 1;

		for (rot = 0; rot < 4; rot++) {
			field[idx].no  = no;
			field[idx].rot = rot;

			/* Check whether this card matches. */
			if (!check(idx)) {
				if (debug)
					print(idx, 1);
				continue;
			}

			/* Try next card or print the solution found. */
			if (idx < 8)
				place_card(idx + 1);
			else
				print(idx, 0);
		}
		used[no] = 0;
	}
}

static int check(int idx)
{
	/* Check for match with the upper card. */
	if (idx >= 3) {
		int above = idx - 3;
		if (mark(idx, UP) + mark(above, DOWN) != 0)
			return 0;
	}

	/* Check for match with the left card. */
	if (idx % 3 != 0) {
		int left = idx - 1;
		if (mark(idx, LEFT) + mark(left, RIGHT) != 0)
			return 0;
	}

	return 1;
}

static int mark(int idx, int dir)
{
	int no  = field[idx].no;
	int rot = field[idx].rot;

	return card[no].mark[(rot + dir) % 4];
}

static void print(int idx, int brk_flag)
{
	int k;

	for (k = 0; k <= idx; k++)
		printf("(%d,%d) ", field[k].no, field[k].rot);
	if (brk_flag)
		puts(": break");
	else
		putchar('\n');
}
