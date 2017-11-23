# ifndef __bitct__h
# define __bitct__h
# include <mdlint.h>
# include <stdlib.h>
struct bitct {
	mdl_u8_t(*get_byte)(void*);
	void(*put_byte)(mdl_u8_t, void*);
	void *get_arg, *put_arg;
	// get
	mdl_u8_t leftover;
	mdl_u8_t bit_c;

	// put
	mdl_u8_t bits_needed;
	mdl_u8_t byte_out;
};

void bitct_init(struct bitct*, mdl_u8_t(*)(void*), void(*)(mdl_u8_t, void*));
void bitct_put_lx(struct bitct*, mdl_u8_t, mdl_u8_t);
mdl_u8_t bitct_get_lx(struct bitct*, mdl_u8_t);
void bitct_dump(struct bitct*);
void set_get_arg(struct bitct*, void*);
void set_put_arg(struct bitct*, void*);
# endif /*__bitct__h*/
