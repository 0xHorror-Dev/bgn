#include <bign/bign.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>


static void bign_inner_shirt_right(uint8_t* digits, const size_t bits, const size_t shift)
{
	if (bits == 0 || shift == 0) 
	{
		return;
	}

	const size_t actual_shift = shift % bits;  
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

int8_t bign_create(const uint8_t* digits, const size_t dlen, const uint8_t base, const size_t bits, bign_t* number)
{
	(void)(number);

	uint8_t* num = calloc(bits, sizeof(uint8_t));
	if (num == NULL)
	{
		return -1;
	}
	memcpy(num, digits, dlen);
	size_t num_len = dlen;

	uint8_t* bin = calloc(bits, sizeof(uint8_t));
	if (bin == NULL)
	{
		free(num);
		return -1;
	}
	size_t bcounter = 0;

	while (1)
	{
		uint8_t* new_number = calloc(bits, sizeof(uint8_t));
		if (new_number == NULL)
		{
			free(num);
			free(bin);
			return -1;
		}
		size_t ncounter = 0;
		uint8_t remainder = 0;

		for (size_t i = 0; i < num_len; i += 1)
		{
			int current_num = remainder * base + num[i];
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

	for (size_t i = 0; i < bcounter / 2; i++) {
		uint8_t tmp = bin[i];
		bin[i] = bin[bcounter - 1 - i];
		bin[bcounter - 1 - i] = tmp;
	}

	bign_inner_shirt_right(bin, bits, bits-bcounter);

	for (size_t i = 0; i < bits; i += 1)
	{
		printf("%u", ((unsigned int)bin[i]));
	}
	
	free(bin);
	free(num);

	return 0;
}
