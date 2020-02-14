#include <stdio.h>
#include "gmp.h"
#include "function.h"
#include "keygen.h"

#define BASE10 10
#define NB_ESSAIE 10

/*
** Test de comparaison entre ExpMod (du DM)
** et mpz_pown (de gmp) qui calculent g^a mod p
*/

void	test_exponentiation_binaire(){
  mpz_t p;
  mpz_t g;
  mpz_t a;
  mpz_t ret;
  mpz_t tmp;
    
  mpz_init(p);
  mpz_init(g);
  mpz_init(a);
  mpz_init(ret);
  mpz_init(tmp);

  for (int i = 0; i != NB_ESSAIE; i++){
    make_rand_nbits(g, 60); // g number of 30 bits.
    make_rand_nbits(a, 55); // g number of 10 bits.
    make_rand_nbits(p, 34); // p number of 18 bits. 
    ExpMod(ret, g, a, p);
    mpz_powm(tmp, g, a, p);

    gmp_printf("g = %Zd\n", g);
    gmp_printf("a = %Zd\n", a);
    gmp_printf("p = %Zd\n", p);
    printf("g ^ a mod p : \n");
    gmp_printf("->Par mpz_powm\t: %Zd\n", tmp);
    gmp_printf("->Par ExpMod\t: %Zd\n", ret);
    
    if (!(mpz_cmp(ret, tmp) == 0)) {// ret != cmp
      printf("Error : ExpMod and mpz_powm don't return the same value\n");
      
    }
  }
}
