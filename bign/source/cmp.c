#define BIGN_PRIVATE
#include <bign/bign.h>
#include <bign/op.h>
#include <string.h>

BIGN_API int8_t bign_cmp(bign_t* a, bign_t* b)
{
    for (size_t i = 0; i < b->len; i++)
    {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }

    return 0;
}
