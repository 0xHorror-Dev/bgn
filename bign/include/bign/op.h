#pragma once

#include<stdint.h>
#include<bign/API.h>

struct bign_t;

BIGN_API int8_t bign_cmp(bign_t* a, bign_t* b);

BIGN_API int8_t bign_add(bign_t* a, bign_t* b, bign_t* dest);
BIGN_API int8_t bign_sub(bign_t* a, bign_t* b, bign_t* dest);
BIGN_API int8_t bign_get_additional_code(bign_t* a, bign_t* dest);

BIGN_API int8_t bign_mul(bign_t* a, bign_t* b, bign_t* dest);

BIGN_API int8_t bign_or(bign_t* a, bign_t* b, bign_t* dest);

BIGN_API int8_t bign_mod(bign_t* a, bign_t* b, bign_t* dest);
BIGN_API int8_t bign_div(bign_t* a, bign_t* b, bign_t* dest);
