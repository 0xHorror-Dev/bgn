#pragma once

#include <bign/API.h>
#include <stdint.h>

typedef struct struct_bign_t
{
	size_t len;
	uint8_t* digits;
} bign_t;

BIGN_API int8_t bign_create(const size_t bits, bign_t* number);
BIGN_API int8_t bign_create_one(const size_t bits, bign_t* number);
BIGN_API int8_t bign_create_from_digits(const uint8_t negative, const uint8_t* digits, const size_t dlen, const uint8_t base, const size_t bits, bign_t* number);
BIGN_API int8_t bign_create_from_str(const char* number_str, const uint8_t base, const size_t bits, bign_t* number);

BIGN_API void bign_free(bign_t* number);

BIGN_API int8_t bign_cpy(bign_t* number, bign_t* dest);

BIGN_API void bign_print(const bign_t* number);

BIGN_API void bign_shift_right(bign_t* number, const size_t bits);
BIGN_API void bign_shift_left(bign_t* number, const size_t bits);
