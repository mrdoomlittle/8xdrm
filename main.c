# include "8xdrm.h"

# include <stdio.h>
mdl_u8_t buff[4] = {0b11111111, 0b01000000, 0b00100000, 0b00010000};
mdl_u8_t c = 0;
mdl_u8_t get_byte() {
	c++;
	return buff[c-1];
}

void print_bin(mdl_u8_t __byte) {
	for (mdl_u8_t x = 0; x != 8; x++)
		printf("%u", __byte >> (7-x) & 1);
	printf("\n");
}

mdl_u8_t o = 0;
void put_byte(mdl_u8_t __byte) {
	buff[o++] = __byte;
}

int main(void) {
	struct _8xdrm_t _8xdrm;

	_8xdrm.put_byte = &put_byte;
	_8xdrm.get_byte = &get_byte;
	_8xdrm_init(&_8xdrm);

	_8xdrm_put_wx(&_8xdrm, 0b00000011, 2);
	_8xdrm_put_wx(&_8xdrm, 0b00000001, 1);

	_8xdrm_put_wx(&_8xdrm, 0b01000010, 8);
	_8xdrm_put_wx(&_8xdrm, 0b00100001, 5);

	print_bin(_8xdrm_get_wx(&_8xdrm, 8));
	print_bin(_8xdrm_get_wx(&_8xdrm, 8));
}
