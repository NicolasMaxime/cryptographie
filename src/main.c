#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"

void test(){
  mpz_t res;
  mpz_t res2;
  mpz_t p;
  mpz_t q;
  mpz_t a;
  mpz_t k;
  
  mpz_init(p);
  mpz_init(k);
  mpz_init(q);
  mpz_init(a);
  mpz_init(res);
  mpz_init(res2);
  mpz_set_ui(p, 71);
  mpz_set_ui(q, 7);
  mpz_set_ui(k, 10);
  for (int i = 1; i != 70; i++){
    mpz_set_ui(a, i);
    puissance_mod(res, a, q, p); // a^q mod p
    if (mpz_cmp_ui(res, 1) == 0){
      puissance_mod(res2, a, k, p);
      if (mpz_cmp_ui(res2, 1) != 0)
	gmp_printf("%Zd ^ 7 % 71 = %Zd\n", a, res);
    }
  }
}

int main(){
  key_gpq_t *key;

  //key = keygen(256, 1792);
  test();
  //test_exponentiation_binaire(); //ok
  //free(key);
  return 0;
}
