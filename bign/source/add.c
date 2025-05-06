#define BIGN_PRIVATE
#include <bign/bign.h>
#include <bign/op.h>
#include <string.h>

static inline void bign_inner_sum_add(bign_t* a, bign_t* b, bign_t* dest, uint32_t* ocarry)
{
	uint32_t carry = 0;
	const int64_t len = (int64_t)(a->len -1);
	if (a == NULL || b == NULL || dest == NULL) return;
	if (a->len != b->len || a->len != dest->len || b->len != dest->len) return;
	if (a->digits == NULL || b->digits == NULL || dest->digits == NULL) return;

	for (int64_t i = len; i >= 0; i -= 1)
	{
		uint32_t sum = a->digits[i] + b->digits[i] + carry;
		dest->digits[i] = sum % 2;
		carry = sum > 1;
	}

	if(ocarry != NULL)
		*ocarry = carry;
}

BIGN_API int8_t bign_add(bign_t *a, bign_t *b, bign_t *dest) 
{
	bign_t code_a = { 0 };
	uint32_t ocarry = 0;
	bign_t code_b = { 0 };
	if (a == NULL || b == NULL || dest == NULL) return -1;
	if(a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if(a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;

	if (bign_create(a->len, &code_a) == -1)
	{
		return -1;
	}
	if (bign_create(b->len, &code_b) == -1)
	{
		bign_free(&code_a);
		return -1;
	}

	if (bign_cpy(a, &code_a) == -1)
	{
		bign_free(&code_a);
		bign_free(&code_b);
	}
	if (bign_cpy(b, &code_b) == -1)
	{
		bign_free(&code_a);
		bign_free(&code_b);
	}

	if (bign_get_additional_code(a, &code_a) == -1)
	{
		bign_free(&code_a);
		bign_free(&code_b);
		return -1;
	}
	if (bign_get_additional_code(b, &code_b) == -1)
	{
		bign_free(&code_a);
		bign_free(&code_b);
		return -1;
	}

	bign_inner_sum_add(&code_a, &code_b, dest, &ocarry);
	if (ocarry)
	{
		return -2;
	}

	bign_free(&code_a);
	bign_free(&code_b);
	return 0;
}

BIGN_API int8_t bign_sub(bign_t* a, bign_t* b, bign_t* dest)
{
	bign_t new_b = { 0 };
	bign_create(b->len, &new_b);
	bign_cpy(b, &new_b);

	new_b.digits[0] = 1;

	return bign_add(a, &new_b, dest);
}

BIGN_API int8_t bign_get_additional_code(bign_t* a, bign_t* dest)
{
	bign_t one = {0};
	if (a->len != dest->len) return -1;
	if (a->digits == NULL || dest->digits == NULL) return -1;
	if (a->digits[0] == 0) return 0;

	//#pragma omp parallel for
	for (size_t i = 0; i < a->len; i += 1)
	{
		uint8_t tmp = !a->digits[i];
		dest->digits[i] = tmp;
	}
	
	if (bign_create_one(a->len, &one) == -1)
	{
		return -1;
	}
	bign_inner_sum_add(dest, &one, dest, NULL);

	dest->digits[0] = 1;

	bign_free(&one);

	return 0;
}
