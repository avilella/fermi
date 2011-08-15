#include "rld.h"
#include "fermi.h"

int sais_bwt(unsigned char *T, int n, int k);
int sais_bwt64(unsigned char *T, int64_t n, int k);

int fm_bwtgen(int asize, int64_t l, uint8_t *s)
{
	if (l <= INT32_MAX) return sais_bwt(s, l, asize);
	else return sais_bwt64(s, l, asize);
}

rld_t *fm_bwtenc(int asize, int sbits, int64_t l, const uint8_t *s)
{
	int c;
	int64_t i, k;
	rlditr_t itr;
	rld_t *e;

	e = rld_init(asize, sbits);
	rld_itr_init(e, &itr, 0);
	k = 1; c = s[0];
	for (i = 1; i < l; ++i) {
		if (s[i] != c) {
			rld_enc(e, &itr, k, c);
			c = s[i];
			k = 1;
		} else ++k;
	}
	rld_enc(e, &itr, k, c);
	rld_enc_finish(e, &itr);
	return e;
}