#define BIGN_PRIVATE
#include <bign/bign.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define HEX_TO_DIGIT(hex, offset)((hex - offset) + 10) 

BIGN_API void bign_print(const bign_t* number)
{
	if(number == NULL)
	{
		printf("(null)");
	}

	for(size_t i = 0; i < number->len; i += 1)
	{
		printf("%u", ((uint32_t)number->digits[i]));
	}
}

static void bign_inner_digits_from_str(const char* num_str, size_t count, uint8_t* digits)
{
	if(num_str == NULL || digits == NULL) return;
	
	//#pragma omp parallel for
	for(size_t i = 0; i < count; i += 1 )
	{
		uint8_t code = (uint8_t)num_str[i];
		if(code > 64 && code < 91)
		{
			digits[i] = HEX_TO_DIGIT(code, 65);
		}
		else if(code > 96 && code < 123)
		{
			digits[i] = HEX_TO_DIGIT(code, 97);
		}
		else if(code > 47 && code < 58)
		{
			digits[i] = (code) - 48;
		}
	}
}

static void bign_inner_shift_right(uint8_t* digits, const size_t bits, const size_t shift)
{
	const size_t actual_shift = shift % bits;  
	if (bits == 0 || shift == 0) 
	{
		return;
	}

	if (actual_shift == 0) 
	{
		return;
	}

	for (size_t i = bits - 1; i >= actual_shift; i--)
	{
		digits[i] = digits[i - actual_shift];
	}

	for (size_t i = 0; i < actual_shift; i++)
	{
		digits[i] = 0;
	}
}


static void bign_inner_shift_left(uint8_t* digits, const size_t bits, const size_t shift)
{
	const size_t actual_shift = shift % bits;
	const size_t boundary = bits - actual_shift;
	if (bits == 0 || shift == 0)
	{
		return;
	}

	if (actual_shift == 0)
	{
		return;
	}



	// Shift the digits left
	for (size_t i = 0; i < boundary; i++) {
		digits[i] = digits[i + actual_shift];
	}

	// Zero out the remaining digits
	for (size_t i = boundary; i < bits; i++) {
		digits[i] = 0;
	}
}


BIGN_API int8_t bign_cpy(bign_t* number, bign_t* dest)
{
	if (number->len == dest->len)
	{
		if (dest->digits == NULL)
		{
			dest->digits = calloc(number->len, sizeof(uint8_t));
			if (dest->digits == NULL)
			{
				return -1;
			}
		}

		memcpy(dest->digits, number->digits, number->len * sizeof(uint8_t));
	}
	else
	{
		if (dest->digits != NULL)
		{
			free(dest->digits);
		}
		dest->digits = calloc(number->len, sizeof(uint8_t));
		if (dest->digits == NULL)
		{
			return -1;
		}
		dest->len = number->len;

		memcpy(dest->digits, number->digits, number->len * sizeof(uint8_t));
	}

	return 0;
}

BIGN_API int8_t bign_create(const size_t bits, bign_t *number)
{
	number->digits = calloc(bits, sizeof(uint8_t));
	if(number->digits == NULL) return -1;
	number->len = bits;
	return 0;
}

BIGN_API int8_t bign_create_one(const size_t bits, bign_t* number)
{
	number->digits = calloc(bits, sizeof(uint8_t));
	if (number->digits == NULL) return -1;
	number->len = bits;
	number->digits[bits - 1] = 1;
	return 0;
}

BIGN_API int8_t bign_create_from_digits(const uint8_t negative, const uint8_t* digits, const size_t dlen, const uint8_t base, const size_t bits, bign_t* number)
{
	uint8_t* num = calloc(bits, sizeof(uint8_t));
	size_t num_len = dlen;
	uint8_t* bin = NULL;
	size_t bcounter = 0;
	size_t ncounter = 0;
	uint8_t remainder = 0;
	if (num == NULL)
	{
		return -1;
	}
	memcpy(num, digits, dlen);

	bin = calloc(bits, sizeof(uint8_t));
	if (bin == NULL)
	{
		free(num);
		return -1;
	}

	while (1)
	{
		uint8_t* new_number = calloc(bits, sizeof(uint8_t));
		if (new_number == NULL)
		{
			free(num);
			free(bin);
			return -1;
		}
		ncounter = 0;
		remainder = 0;
		for (size_t i = 0; i < num_len; i += 1)
		{
			uint32_t current_num = remainder * base + num[i];
			uint8_t new_digit = (uint8_t)(current_num / 2);
			remainder = current_num % 2;

			//if new_num or new_digit != 0:
			if (ncounter > 0 || new_digit != 0)
			{
				//new_num.append(str(new_digit))
				new_number[ncounter] = new_digit;
				ncounter += 1;
				//
			}

			//new_number[ncounter] = new_digit;
			//ncounter += 1;
		}

		//binary.append(str(remainder))
		bin[bcounter] = remainder;
		bcounter += 1;
		//

		//num = new_num
		memcpy(num, new_number, ncounter);
		num_len = ncounter;
		//

		free(new_number);
		if (num_len == 0)
		{
			break;
		}

	}
	
	for (size_t i = 0; i < bcounter / 2; i++)
	{
		uint8_t tmp = bin[i];
		bin[i] = bin[bcounter - 1 - i];
		bin[bcounter - 1 - i] = tmp;
	}

	bign_inner_shift_right(bin, bits, bits-bcounter);

	bin[0] = negative;

	number->len = bits;
	number->digits = bin;
	
	free(num);

	return 0;
}

BIGN_API int8_t bign_create_from_str(const char* number_str, const uint8_t base, const size_t bits, bign_t* number)
{
	size_t nl = strlen(number_str);
	uint8_t is_neg = 0;
	int8_t res = 0;
	uint8_t* digits = NULL;
	if(nl == 0) return -1;
	digits = calloc(nl, sizeof(uint8_t));
	if(digits == NULL)
	{
		return -1;
	}

	if (number_str[0] == '-')
	{
		is_neg = 1;
		number_str += 1;
	}

	bign_inner_digits_from_str(number_str, nl, digits);
	res = bign_create_from_digits(is_neg, digits, nl, base, bits, number);
	
	free(digits);

	return res;
}

BIGN_API void bign_free(bign_t* number)
{
	if(number == NULL) return;
	if(number->digits != NULL)
	{
		free(number->digits);
	}
}

BIGN_API void bign_shift_right(bign_t* number, const size_t bits)
{
	if(number == NULL) return;
	bign_inner_shift_right(number->digits, number->len, bits);
}

BIGN_API void bign_shift_left(bign_t* number, const size_t bits) 
{
	if (number == NULL) return;
	bign_inner_shift_left(number->digits, number->len, bits);
}
