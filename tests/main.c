#include <bign/bign.h>
#include <bign/op.h>
#include <stdio.h>

//[[unused]] static inline void first_test(void)
//{
//	const int bits = 32;
//	uint8_t num[2] = { 1,5 };
//	uint8_t num2[2] = { 1,2 };
//	bign_t a, b, out;
//
//
//	bign_create_from_digits(0, num, 2, 10, bits, &a);
//	bign_create_from_digits(1, num2, 2, 10, bits, &b);
//
//	bign_print(&a);
//	putchar('\n');
//	bign_print(&b);
//	putchar('\n');
//
//	bign_create(bits, &out);
//
//	if (bign_add(&a, &b, &out) == -1)
//	{
//		printf("add - failed!\n");
//	}
//
//	bign_print(&out);
//
//	putchar('\n');
//	bign_free(&a);
//	bign_free(&b);
//	bign_free(&out);
//
//}

int main(void)
{
	bign_t a,b,c;
	int32_t t;
	
	//+1 bit for signed bit!
	bign_create_from_str("10", 10, 8, &a);
	bign_create_from_str("2", 10, 8, &b);
	bign_create(8, &c);

	bign_print(&a);
	putchar('\n');
	bign_print(&b);
	putchar('\n');
	putchar('\n');

	putchar('\n');
	bign_print(&c);

	putchar('\n');

	t = (int32_t)bign_cmp(&b, &a);
	printf("%d", t);

	bign_mod(&a, &b, &c);
	bign_print(&c);
	bign_free(&a);
	bign_free(&b);

	return 0;
}
