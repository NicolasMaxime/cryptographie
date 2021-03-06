#ifndef KEYGEN_H_
# define KEYGEN_H_

#include "gmp.h"

typedef struct key_qpg_s {
  mpz_t g;
  mpz_t p;
  mpz_t q;
} key_gpq_t;

key_gpq_t	*keygen(mp_bitcnt_t n, mp_bitcnt_t o);
void		make_rand_nbits(mpz_t r, mp_bitcnt_t size);

#endif /* !KEYGEN_H_ */
