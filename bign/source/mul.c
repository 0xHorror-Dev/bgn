#define BIGN_PRIVATE
#include <bign/bign.h>
#include <bign/op.h>
#include <stdio.h>
#include <string.h>

static int8_t bign_inner_unsafe_cpy(bign_t* a, bign_t* dest)
{
	if (dest->len >= a->len)
	{
		memcpy(dest->digits, a->digits, a->len);
		return 1;
	}
	return -1;
}

BIGN_API int8_t bign_mul(bign_t* a, bign_t* b, bign_t* dest)
{
	bign_t  tmp;
	bign_t  res;
	if (a == NULL || b == NULL || dest == NULL) return -1;
	if (a->len != b->len || a->len != dest->len || b->len != dest->len) return -1;
	if (a->digits == NULL || b->digits == NULL || dest->digits == NULL) return -1;


	if (bign_create(a->len + 1, &tmp) == -1)
	{
		return -1;
	}

	if (bign_create(a->len + 1, &res) == -1)
	{
		return -1;
	}

	for (int64_t i = ((int64_t)b->len-1), j = 0; i > 0; i -= 1, j += 1)
	{
		if (b->digits[i])
		{
			memset(tmp.digits, 0, tmp.len);
			if (bign_inner_unsafe_cpy(a, &tmp) == -1)
			{
				bign_free(&tmp);
				return -1;
			}
			
			bign_shift_left(&tmp, (size_t)j);

			if (bign_add(&res, &tmp, &res) == -2)
			{
				bign_free(&tmp);
				return -2;
			}
		}
	}

	memcpy(dest->digits, res.digits, dest->len);

	bign_free(&tmp);
	bign_free(&res);

	return 0;
}
