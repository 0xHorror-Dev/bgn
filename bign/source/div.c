#define BIGN_PRIVATE
#include <bign/bign.h>
#include <bign/op.h>
#include <string.h>
#include <stdio.h>

BIGN_API int8_t bign_mod(bign_t* a, bign_t* b, bign_t* dest)
{
	bign_t current_bit = { 0 };
	bign_t quotient = { 0 };
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

	for (int64_t i = (int64_t)a->len; i >= 0; i--)
	{
		bign_shift_left(&reminder, 1);

		bign_create(reminder.len, &current_bit);
		current_bit.digits[i] = a->digits[i];

		bign_or(&reminder, &current_bit, &reminder);

		if (bign_cmp(&reminder, &divisor) >= 0)
		{
			bign_sub(&reminder, &divisor, &reminder);
			quotient.digits[i] = 1;
		}

		bign_free(&current_bit);

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
	while (bign_cmp(&divisor, b) < 0)
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

	while (bign_cmp(&reminder, b) > 0)
	{
		bign_sub(&reminder, b, &reminder);
	}

	bign_cpy(&reminder, dest);

	bign_free(&divisor);
	bign_free(&reminder);

	return 0;
}

BIGN_API int8_t bign_div(bign_t* a, bign_t* b, bign_t* dest)
{
	bign_t current_bit = { 0 };
	bign_t quotient = { 0 };
	bign_t remainder = { 0 };
	bign_t divisor = { 0 };

	if (a == NULL || b == NULL || dest == NULL) return -1;
	if (a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if (a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;


	if (bign_cmp(a, b) < 0)
	{
		memset(dest->digits, 0, dest->len);
		return 0;
	}

	if (bign_create(a->len, &remainder) == -1)
	{
		return -1;
	}

	if (bign_create(b->len, &divisor) == -1)
	{
		bign_free(&remainder);
		return -1;
	}

	if (bign_create(b->len, &quotient) == -1)
	{
		bign_free(&remainder);
		return -1;
	}

	if (bign_cpy(a, &remainder) == -1)
	{
		bign_free(&remainder);
		bign_free(&divisor);
		return -1;
	}

	if (bign_cpy(b, &divisor) == -1)
	{
		bign_free(&remainder);
		bign_free(&divisor);
		return -1;
	}
	bign_create(remainder.len, &current_bit);

	for (int64_t i = (int64_t)a->len - 1; i >= 0; i--)
	{
		//memset(current_bit.digits, 0, current_bit.len);
		bign_shift_left(&remainder, 1);

		current_bit.digits[0] = a->digits[i];
		remainder.digits[0] = current_bit.digits[0];

		if (bign_cmp(&remainder, b) >= 0)
		{
			bign_sub(&remainder, b, &remainder);
			bign_print(&remainder);
			putchar('\n');
			
			quotient.digits[i] = 1;
		}
	}


	bign_print(&quotient);
	putchar('\n');
	bign_cpy(&quotient, dest);

	bign_free(&current_bit);
	bign_free(&divisor);
	bign_free(&remainder);
	bign_free(&quotient);
	return 0;
}

BIGN_API int8_t bign_or(bign_t* a, bign_t* b, bign_t* dest)
{
	if (a == NULL || b == NULL || dest == NULL) return -1;
	if (a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if (a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;

	for (size_t i = 0; i < a->len; i += 1)
	{
		dest->digits[i] = a->digits[i] | b->digits[i];
	}

	return 0;
}
