#include <bign/bign.h>
#include <stdio.h>

int main()
{
	const int bits = 1024;
	uint8_t num[1024] = {1,5};
	bign_t out;
	bign_create(num, 2, 10, bits, &out);
	putchar('\n');
	bign_create(num, 4, 16, bits, &out);
	putchar('\n');
	
	uint8_t num3[1024] = { 5,6,4,2 };
	bign_create(num3, 4, 10, bits, &out);
	putchar('\n');


	return 0;
}