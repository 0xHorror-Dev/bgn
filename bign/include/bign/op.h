#pragma once

#include<stdint.h>
#include<bign/API.h>

struct bign_t;

BIGN_API int8_t bign_add(bign_t* a, bign_t* b, bign_t* dest);
