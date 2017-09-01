# include "8xdrm.h"
# include <stdio.h>
mdl_u8_t buff[4] = {0b11011000, 0b10110001, 0x0, 0x0};
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
	struct _8xdrm _8xdrm;

//	_8xdrm.put_byte = &put_byte;
//	_8xdrm.get_byte = &get_byte;
	_8xdrm_init(&_8xdrm, &get_byte, &put_byte);

//	_8xdrm_put_wx(&_8xdrm, 0b11010010, 8);
//	_8xdrm_put_wx(&_8xdrm, 0b10010010, 8);
//	_8xdrm_dump(&_8xdrm);
	
	print_bin(_8xdrm_get_wx(&_8xdrm, 8));
	print_bin(_8xdrm_get_wx(&_8xdrm, 8));
}
