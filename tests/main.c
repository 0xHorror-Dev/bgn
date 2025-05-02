#include <bign/bign.h>
#include <stdio.h>

int main()
{
	const int bits = 1024;
	uint8_t num[1024] = {1,5};
	bign_t out;
	bign_create(num, 2, 10, bits, &out);
	bign_print(&out);
	putchar('\n');


	bign_free(&out);
	return 0;
}
