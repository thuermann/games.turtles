/*
 * $Id: turtles.c,v 1.6 2012/04/04 05:02:03 urs Exp $
 *
 * Solve the turtle game.
 */

#include <stdio.h>

static void place_card(int idx);
static void rotate(int idx);
static int  check(int idx);
static void print(int idx, int brk_flag);

typedef struct {
	int no;
	int p[4];
} CARD;

static const CARD crd[9] = {
	{ 0, { -1, -2, +3, +4 } },
	{ 1, { -1, -2, +3, +4 } },
	{ 2, { -1, -4, +3, +4 } },
	{ 3, { -1, -4, +3, +2 } },
	{ 4, { -3, -1, +2, +4 } },
	{ 5, { -3, -2, +1, +2 } },
	{ 6, { -2, -3, +1, +4 } },
	{ 7, { -1, -3, +4, +2 } },
	{ 8, { -3, -4, +1, +2 } },
};

static CARD c[9];
static int  r[9];
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
	int i, j;

	for (i = 0; i < 9; i++) {
		if (used[i])
			continue;
		used[i] = 1;

		c[idx] = crd[i];
		for (j = 0; j < 4; j++, rotate(idx)) {
			r[idx] = j;

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
		used[i] = 0;
	}
}

static void rotate(int idx)
{
	int tmp;

	tmp = c[idx].p[0];
	c[idx].p[0] = c[idx].p[1];
	c[idx].p[1] = c[idx].p[2];
	c[idx].p[2] = c[idx].p[3];
	c[idx].p[3] = tmp;
}

static int check(int idx)
{
	/* Check for match with the upper card. */
	if (idx >= 3) {
		int above = idx - 3;
		if (c[idx].p[1] + c[above].p[3] != 0)
			return 0;
	}

	/* Check for match with the left card. */
	if (idx % 3 != 0) {
		int left = idx - 1;
		if (c[idx].p[2] + c[left].p[0] != 0)
			return 0;
	}

	return 1;
}

static void print(int idx, int brk_flag)
{
	int k;

	for (k = 0; k <= idx; k++)
		printf("(%d,%d) ", c[k].no, r[k]);
	if (brk_flag)
		puts(": break");
	else
		putchar('\n');
}
