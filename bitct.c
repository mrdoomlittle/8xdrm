# include "bitct.h"
void bitct_init(struct bitct *__bitct, mdl_u8_t(*__get_byte)(void*), void(*__put_byte)(mdl_u8_t, void*)) {
	*__bitct = (struct bitct) {
		.get_byte = __get_byte,
		.put_byte = __put_byte,
		.get_arg = NULL,
		.put_arg = NULL,
		.leftover = 0,
		.bit_c = 0,
		.bits_needed = 8,
		.byte_out = 0
	};
}

mdl_u8_t static _1l_msb = 0x80;
mdl_u8_t static _2l_msb = 0xC0;
mdl_u8_t static _3l_msb = 0xE0;
mdl_u8_t static _4l_msb = 0xF0;
mdl_u8_t static _5l_msb = 0xF8;
mdl_u8_t static _6l_msb = 0xFC;
mdl_u8_t static _7l_msb = 0xFE;
mdl_u8_t static cpy_bits(mdl_u8_t *__dst, mdl_u8_t __src, mdl_u8_t __bit_c) {
	if (!__bit_c) return 0;
	if (__bit_c>>3) {
		*__dst = __src;
		return __src;
	}
	switch(__bit_c) {
		case 1: *__dst = __src&_1l_msb; break;
		case 2: *__dst = __src&_2l_msb; break;
		case 3: *__dst = __src&_3l_msb; break;
		case 4: *__dst = __src&_4l_msb; break;
		case 5: *__dst = __src&_5l_msb; break;
		case 6: *__dst = __src&_6l_msb; break;
		case 7: *__dst = __src&_7l_msb; break;
	}
}

void bitct_put_lx(struct bitct *__bitct, mdl_u8_t __data, mdl_u8_t __l) {
	if (__bitct->bits_needed < __l) {
		__bitct->byte_out |= (__data<<(8-__l))>>(8-__bitct->bits_needed);
		__bitct->put_byte(__bitct->byte_out, __bitct->put_arg);

		mdl_u8_t next = __l-__bitct->bits_needed;
		__bitct->byte_out = 0;
		__bitct->bits_needed = 8;
		bitct_put_lx(__bitct, __data, next);
	} else {
		__bitct->byte_out |= (__data<<(8-__l))>>(8-__bitct->bits_needed);
		__bitct->bits_needed -= __l;
	}

	if (!__bitct->bits_needed) {
		__bitct->put_byte(__bitct->byte_out, __bitct->put_arg);
		__bitct->bits_needed = 8;
		__bitct->byte_out = 0;
	}
}

void static bitct_more(struct bitct *__bitct) {
	__bitct->leftover = __bitct->get_byte(__bitct->get_arg);
	__bitct->bit_c = 8;
}
mdl_u8_t bitct_get_lx(struct bitct *__bitct, mdl_u8_t __l) {
	mdl_u8_t ret_val = 0;
	if (__bitct->bit_c>1) {
		if (__bitct->bit_c > __l) {
			cpy_bits(&ret_val, __bitct->leftover, __l);
			__bitct->bit_c -= __l;
			__bitct->leftover <<= __l;
		} else if(__bitct->bit_c < __l) {
			cpy_bits(&ret_val, __bitct->leftover, __bitct->bit_c);
			mdl_u8_t bits_needed = __l-__bitct->bit_c;
			bitct_more(__bitct);
			mdl_u8_t rt = 0;
			ret_val |= cpy_bits(&rt, __bitct->leftover, bits_needed);
			__bitct->bit_c -= bits_needed;
			__bitct->leftover <<= bits_needed;
		} else {
			__bitct->bit_c = 0;
			ret_val = __bitct->leftover;
		}
	} else {
		bitct_more(__bitct);
		return bitct_get_lx(__bitct, __l);
	}
	return ret_val>>(8-__l);
}

void set_get_arg(struct bitct *__bitct, void *__arg) {__bitct->get_arg=__arg;}
void set_put_arg(struct bitct *__bitct, void *__arg) {__bitct->put_arg=__arg;}
void bitct_dump(struct bitct *__bitct) {
	__bitct->put_byte(__bitct->byte_out, __bitct->put_arg);
}
