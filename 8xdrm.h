# ifndef __8xdrm__h
# define __8xdrm__h
# include <eint_t.h>
struct _8xdrm_t {
	mdl_u8_t (*get_byte)();
	void (*put_byte)(mdl_u8_t);
	// get
	mdl_u8_t leftover;
	mdl_u8_t bit_c;
	mdl_u8_t has_leftovers;

	// put
	mdl_u8_t bits_needed;
	mdl_u8_t byte_out;
};

void _8xdrm_init(struct _8xdrm_t*);
void _8xdrm_put_wx(struct _8xdrm_t*, mdl_u8_t, mdl_u8_t);
mdl_u8_t _8xdrm_get_wx(struct _8xdrm_t*, mdl_u8_t);
# endif /*__8xdrm__h*/
