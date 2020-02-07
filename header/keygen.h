#ifndef KEYGEN_H_
# define KEYGEN_H_

typedef struct key_qpg_s {
  mpz_t g;
  mpz_t p;
  mpz_t q;
} key_gpq_t;

key_gpq_t	*keygen(mp_bitcnt_t n, mp_bitcnt_t o);

#endif /* !KEYGEN_H_ */
