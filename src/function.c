#include "gmp.h"
#include "function.h"

#define N_SIZE 256
#define O_SIZE 1792

/*
** ExpMod
*/

void	puissance_mod(mpz_t ret, mpz_t g, mpz_t a, mpz_t p){

  mpz_t	tmp;
  mpz_t rop;
  
  mpz_init(tmp);
  mpz_init(rop);
  if (mpz_cmp_ui(a, 1) == 0){
    mpz_mod(ret, g, p);
  }
  else {
    mpz_mul(rop, g, g);
    mpz_mod(rop, rop, p);		// rop = g² % p
    mpz_mod_ui(tmp, a, 2);
    if (mpz_cmp_ui(tmp, 0) == 0)	// Si a est pair
      {
	mpz_set(ret, rop);		// return (g² % p)
	mpz_cdiv_q_ui(tmp, a, 2);	//  a = a / 2
	puissance_mod(ret, rop, tmp, p);
      }
    else {				// Si a est impair
	mpz_sub_ui(tmp, a, 1);
	mpz_cdiv_q_ui(tmp, tmp, 2);	// a = (a - 1) /2
	puissance_mod(ret, rop, tmp, p);
	mpz_mul(ret, g, ret);
	mpz_mod(ret, ret, p);		// (g * powm()) % p
      }
  }
}


/*
** ExpMod : ret = g^a % p
*/

void	ExpMod(mpz_t ret, mpz_t g, mpz_t a, mpz_t p){
  puissance_mod(ret, g, a, p);
}

