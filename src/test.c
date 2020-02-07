#include <stdio.h>
#include "gmp.h"
#include "function.h"

#define BASE10 10

void test_exponentiation_binaire(){
  mpz_t p;
  mpz_t g;
  mpz_t a;
  mpz_t ret;
  
  mpz_init(p);
  mpz_init(g);
  mpz_init(a);
  mpz_init(ret);

  mpz_set_str(p, "12345678524", BASE10);
  mpz_set_str(g, "1234567891011121314151617", BASE10);
  mpz_set_str(a, "32", BASE10);
  ExpMod(ret, p, g, a);
  mpz_out_str(stdout, BASE10, ret);
  printf("\n");
  mpz_powm(ret, g, a, p);
  mpz_out_str(stdout, BASE10, ret);
  printf("\n");
}
