#define BIGN_PRIVATE
#include <bign/bign.h>
#include <bign/op.h>
#include <string.h>

BIGN_API int8_t bign_cmp(bign_t* a, bign_t* b)
{
    for (int64_t i = (int64_t)a->len - 1; i >= 0; i -= 1)
    {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }

    return 0;
}
