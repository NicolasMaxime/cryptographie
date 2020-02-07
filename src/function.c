#include "gmp.h"
#include "function.h"

#define N_SIZE 256
#define O_SIZE 1792

/*
** ExpMod
*/

void	puissance_mod(mpz_t ret, mpz_t g, mpz_t a, mpz_t p){

  mpz_t	rop;
  mpz_t	tmp;
  
  mpz_init(rop);
  mpz_init(tmp);

  if (mpz_cmp_ui(a, 1) == 0)
    mpz_set(ret, g);
  else {
    mpz_mul(rop, g, g); // rop = g²
    mpz_mod_ui(tmp, a, 2);
      if (mpz_cmp_ui(tmp, 0) == 0) // si a est paire
      {
	mpz_cdiv_q_ui(tmp, a, 2); //  tmp = a / 2
	puissance_mod(ret, rop, tmp, p);
	mpz_mod(ret, ret, p);
      }
    else
      {
	mpz_sub_ui(tmp, a, 1); // a - 1
	mpz_cdiv_q_ui(tmp, a, 2); // (a - 1) /2 
	puissance_mod(ret, rop, tmp, p);
	mpz_mod(ret, ret, p);
	mpz_mul(ret, g, ret);
      }
  }
}


void	ExpMod(mpz_t ret, mpz_t p, mpz_t g, mpz_t a){
  puissance_mod(ret, g, a, p);
}

