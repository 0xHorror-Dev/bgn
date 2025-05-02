#include <bign/bign.h>
#include <bign/op.h>
#include <omp.h>

BIGN_API int8_t bign_add(bign_t *a, bign_t *b, bign_t *dest) 
{
	if(a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if(a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;

	uint32_t carry = 0;
	#pragma omp for	
	for(size_t i = a->len - 1; i > 0; i-= 1)
	{
		uint32_t tmp = a->digits[i] + b->digits[i] + carry;
		dest->digits[i] = tmp % 2;
		carry = tmp / 2;
	}

	return 0;
}
