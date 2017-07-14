# include "8xdrm.h"
void _8xdrm_init(struct _8xdrm_t *__8xdrm) {
	__8xdrm->has_leftovers = 0;
	__8xdrm->byte_out = 0;
	__8xdrm->bits_needed = 8;
}

mdl_u8_t w1_msb = 0x80;
mdl_u8_t w2_msb = 0xC0;
mdl_u8_t w3_msb = 0xE0;
mdl_u8_t w4_msb = 0xF0;
mdl_u8_t w5_msb = 0xF8;
mdl_u8_t w6_msb = 0xFC;
mdl_u8_t w7_msb = 0xFE;

mdl_u8_t cpy_bits(mdl_u8_t __byte, mdl_u8_t __bit_c) {
	mdl_u8_t ret_val = 0;
	switch(__bit_c) {
		case 0: return 0;
		case 1: ret_val = __byte&w1_msb; break;
		case 2: ret_val = __byte&w2_msb; break;
		case 3: ret_val = __byte&w3_msb; break;
		case 4: ret_val = __byte&w4_msb; break;
		case 5: ret_val = __byte&w5_msb; break;
		case 6: ret_val = __byte&w6_msb; break;
		case 7: ret_val = __byte&w7_msb; break;
		default:
			return __byte;
	}
	return ret_val;
}

void _8xdrm_put_wx(struct _8xdrm_t *__8xdrm, mdl_u8_t __data, mdl_u8_t __w) {
	if (__8xdrm->bits_needed < __w) {
		__8xdrm->byte_out |= (__data << 8-__w) >> 8-__8xdrm->bits_needed;
		__8xdrm->put_byte(__8xdrm->byte_out);

		mdl_u8_t e = __w-__8xdrm->bits_needed;
		__8xdrm->byte_out = 0;
		__8xdrm->bits_needed = 8;
		_8xdrm_put_wx(__8xdrm, __data, e);
	} else {
		__8xdrm->byte_out |= (__data << 8-__w) >> 8-__8xdrm->bits_needed;
		__8xdrm->bits_needed -= __w;
	}

	if (!__8xdrm->bits_needed) {
		__8xdrm->put_byte(__8xdrm->byte_out);
		__8xdrm->bits_needed = 8;
	}
}

mdl_u8_t _8xdrm_get_wx(struct _8xdrm_t *__8xdrm, mdl_u8_t __w) {
	mdl_u8_t ret_val = 0;

	if (__8xdrm->has_leftovers) {
		if (__8xdrm->bit_c > __w) {
			ret_val = cpy_bits(__8xdrm->leftover, __w);
			__8xdrm->bit_c -= __w;
			__8xdrm->leftover = __8xdrm->leftover << __w;
		} else if(__8xdrm->bit_c < __w) {
			ret_val = cpy_bits(__8xdrm->leftover, __8xdrm->bit_c);
			mdl_u8_t bits_needed = __w-__8xdrm->bit_c;
			__8xdrm->has_leftovers = 0;
			_8xdrm_get_wx(__8xdrm, 0);
			ret_val |= cpy_bits(__8xdrm->leftover, bits_needed);
			__8xdrm->bit_c -= bits_needed;
			__8xdrm->leftover = __8xdrm->leftover << bits_needed;
		} else {
			__8xdrm->has_leftovers = 0;
			ret_val = __8xdrm->leftover;
		}
	} else {
		__8xdrm->leftover = __8xdrm->get_byte();
		__8xdrm->bit_c = 8;
		__8xdrm->has_leftovers = 1;
		return _8xdrm_get_wx(__8xdrm, __w);
	}

	return ret_val;
}
