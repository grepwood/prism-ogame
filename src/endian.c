#include <stdio.h>
#include <stdint.h>

/* Returns explained: 0 is little, 1 is big */

unsigned char is_big_endian(void)
{
	union
	{
		uint16_t i;
		char c[2];
	}
	foo = {0x0100};
	return foo.c[0];
}
