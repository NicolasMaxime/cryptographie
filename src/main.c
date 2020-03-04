#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"
#include "key.h"
#include "sha256.h"

void	generate_key(mpz_t Ks, mpz_t Kp){
  key_gpq_t *val;
  
  val = keygen(256, 1792);
  key(val->q, val->p, val->g, Kp, Ks);
}

void schnorr(){
  return ;
}

int	main(){
  mpz_t Ks;
  mpz_t Kp;
  
  generate_key(Ks, Kp);
  schnorr();
  //test_exponentiation_binaire(); //ok
  //free(key);
  return 0;
}
