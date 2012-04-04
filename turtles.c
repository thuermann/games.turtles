/*
 * $Id: turtles.c,v 1.3 2012/04/04 04:59:08 urs Exp $
 *
 * Solve the turtle game.
 */

#include <stdio.h>

static void no(int idx);
static void rotate(int idx);

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

	no(0);

	return 0;
}

static void no(int idx)
{
	int i, j, k;

	for (i = 0; i < 9; i++) {
		if (used[i])
			continue;
		used[i] = 1;

		c[idx] = crd[i];
		for (j = 0; j < 4; j++, rotate(idx)) {
			r[idx] = j;
			if (idx >= 3) {
				if (c[idx].p[1] + c[idx - 3].p[3] != 0) {
					if (debug) {
						for (k = 0; k <= idx; k++)
							printf("(%d,%d) ", c[k].no, r[k]);
						puts(": break");
					}
					continue;
				}
			}
			if (idx != 0 && idx != 3 && idx != 6) {
				if (c[idx].p[2] + c[idx - 1].p[0] != 0) {
					if (debug) {
						for (k = 0; k <= idx; k++)
							printf("(%d,%d) ", c[k].no, r[k]);
						puts(": break");
					}
					continue;
				}
			}
			if (idx < 8)
				no(idx + 1);
			else {
				for (k = 0; k < 9; k++)
					printf("(%d,%d) ", c[k].no, r[k]);
				putchar('\n');
			}
		}
		used[i] = 0;
	}
}

static void rotate(int idx)
{
	int aux;

	aux = c[idx].p[0];
	c[idx].p[0] = c[idx].p[1];
	c[idx].p[1] = c[idx].p[2];
	c[idx].p[2] = c[idx].p[3];
	c[idx].p[3] = aux;
}
