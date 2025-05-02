#include <bign/bign.h>
#include <bign/op.h>
#include <stdio.h>

int main()
{
	const int bits = 32;
	uint8_t num[2] = {1,5};
	uint8_t num2[2] = {1,2};
	bign_t a,b, out;
	
	bign_create_from_digits(num, 2, 10, bits, &a);
	bign_create_from_digits(num2, 2, 10, bits, &b);
	
	bign_print(&a);
	putchar('\n');
	bign_print(&b);
	putchar('\n');

	bign_create(bits, &out);

	if(bign_add(&a, &b, &out) == -1)
	{
		printf("add - failed!\n");
	}

	bign_print(&out);
	
	putchar('\n');
	bign_free(&a);
	bign_free(&b);
	bign_free(&out);
	return 0;
}
