#pragma once
#include <stdint.h>

typedef struct _struct_bign_t
{
	size_t len;
	uint8_t* digits;
} bign_t;

int8_t bign_create(const uint8_t* digits, const size_t dlen, const uint8_t base, const size_t bits, bign_t* number);

int8_t bign_shift(bign_t* number);