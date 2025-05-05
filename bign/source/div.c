#define BIGN_PRIVATE
#include <bign/bign.h>
#include <bign/op.h>
#include <string.h>
#include <stdio.h>

BIGN_API int8_t bign_mod(bign_t* a, bign_t* b, bign_t* dest)
{
	bign_t reminder = { 0 };
	bign_t divisor = { 0 };
	if (a == NULL || b == NULL || dest == NULL) return -1;
	if (a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if (a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;
	(void)(a);
	(void)(b);
	(void)(dest);

	// a<b => ret a
	if (bign_cmp(a,b) < 0)
	{
		bign_cpy(dest, a);
		return 0;
	}

	if (bign_create(a->len, &reminder) == -1)
	{
		return -1;
	}

	if (bign_create(b->len, &divisor) == -1)
	{
		bign_free(&reminder);
		return -1;
	}

	if (bign_cpy(a, &reminder) == -1)
	{
		bign_free(&reminder);
		bign_free(&divisor);
		return -1;
	}

	if (bign_cpy(b, &divisor) == -1)
	{
		bign_free(&reminder);
		bign_free(&divisor);
		return -1;
	}


	// find value to divide!
	while (bign_cmp(&reminder, &divisor) >= 0)
	{
		bign_shift_left(&divisor, 1);
		putchar('\n');
		bign_print(&divisor);
		putchar('\n');
		bign_print(&reminder);
		putchar('\n');
	}

	bign_shift_right(&divisor, 1);
	
	/*
		TO DO: FIX THIS LOOP
		condition is not working! rewrite while loop condition!
	*/
	while (bign_cmp(&reminder, b) < 0)
	{
		if (bign_cmp(&reminder, &divisor) >= 0)
		{
			bign_sub(&reminder, &divisor, &reminder);
		}
		bign_shift_right(&divisor, 1);

		putchar('\n');
		bign_print(&divisor);
		putchar('\n');
		bign_print(&reminder);
		putchar('\n');
	}

	bign_cpy(&reminder, dest);

	bign_free(&divisor);
	bign_free(&reminder);

	return 0;
}

BIGN_API int8_t bign_div(bign_t* a, bign_t* b, bign_t* dest)
{
	if (a == NULL || b == NULL || dest == NULL) return -1;
	if (a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if (a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;
	(void)(a);
	(void)(b);
	(void)(dest);

	return 0;
}
