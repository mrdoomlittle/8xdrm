# include "bitct.h"
# include <stdio.h>
mdl_u8_t buff[4] = {0x0, 0x0, 0x0, 0x0};
mdl_u8_t c = 0;
mdl_u8_t get_byte(void *__arg) {
	c++;
	return buff[c-1];
}

void print_bin(mdl_u8_t __byte) {
	for (mdl_u8_t x = 0; x != 8; x++)
		printf("%u", __byte >> (7-x) & 1);
	printf("\n");
}

mdl_u8_t o = 0;
void put_byte(mdl_u8_t __byte, void *__arg) {
	buff[o++] = __byte;
}

int main(void) {
	struct bitct _bitct;

//	_bitct.put_byte = &put_byte;
//	_bitct.get_byte = &get_byte;
	bitct_init(&_bitct, &get_byte, &put_byte);

	bitct_put_lx(&_bitct, 0b00000010, 2);
	bitct_put_lx(&_bitct, 0b00000010, 2);
	bitct_put_lx(&_bitct, 0b00000010, 2);
	bitct_put_lx(&_bitct, 0b00000010, 1);
	bitct_put_lx(&_bitct, 0b10000010, 8);
	bitct_dump(&_bitct);
	print_bin(buff[0]);
	print_bin(buff[1]);
//	_bitct_put_wx(&_bitct, 0b11010010, 8);
//	_bitct_put_wx(&_bitct, 0b10010010, 8);
//	_bitct_dump(&_bitct);
	
//	print_bin(bitct_get_lx(&_bitct, 8));
//	print_bin(bitct_get_lx(&_bitct, 8));
}
