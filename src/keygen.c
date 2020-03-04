#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gmp.h"
#include "function.h"
#include "keygen.h"

/*
**  Keygen(); 
**
*/

static unsigned long int seed = 1;

void	make_rand_nbits(mpz_t r, mp_bitcnt_t size){
  gmp_randstate_t state;

  gmp_randinit_mt(state);
  gmp_randseed_ui(state, seed * rand());
  mpz_urandomb(r, state, size);
  seed = seed + 1;
}

void	make_q(mpz_t q, mp_bitcnt_t n){
  int	continuer;

  continuer = 0;
  mpz_init(q);
  while (continuer == 0){ // As long as we don't have a prime number
    make_rand_nbits(q, n);
    mpz_nextprime(q, q);
    continuer = mpz_probab_prime_p(q, 50);
  }  
}

void	make_p(mpz_t p, mpz_t q, mpz_t k, mp_bitcnt_t o){
  int	continuer;

  mpz_init(p);
  continuer = 0;
  while (continuer == 0){ // as long as p = 1 + qk is not prime
    make_rand_nbits(k, o);
    mpz_mul(p, q, k);
    mpz_add_ui(p, p, 1);
    continuer = mpz_probab_prime_p(k, 50);
  }
}

void	make_g(mpz_t g, mpz_t q, mpz_t p, mpz_t k){
  gmp_randstate_t state;
  int	continuer;
  mpz_t	tmp;

  gmp_randinit_mt(state);
  gmp_randseed_ui(state, seed * rand());
  continuer = 0;
  mpz_init(g);
  mpz_init(tmp);
  while (continuer == 0){
    mpz_sub_ui(tmp, p, 4);	// tmp = p - 4
    mpz_urandomm(g, state, tmp);// 0 <= g <= p - 4
    mpz_add_ui(g, g, 2);	// 2 <= g <= p - 2
    ExpMod(tmp, g, k, p);
    if (mpz_cmp_ui(tmp, 1) != 0)
      continuer = 1;
    else
      seed = seed + 1;
  }
}

key_gpq_t	*keygen(mp_bitcnt_t n, mp_bitcnt_t o){

  mpz_t		k;
  key_gpq_t	*ret;

  ret = malloc(sizeof(*ret));
  srand(time(NULL));
  mpz_init(k);
  make_q(ret->q, n);
  make_p(ret->p, ret->q, k, o);
  make_g(ret->g, ret->q, ret->p, k);
  return ret;
}
