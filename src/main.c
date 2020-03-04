#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"
#include "key.h"
#include "sha256.h"

void schnorr(){
  key_gpq_t *val;
  TCSha256State_t test;
  mpz_t Ks;
  mpz_t Kp;
  
  val = keygen(256, 1792);
  key(val->q, val->p, val->g, Kp, Ks);
  tc_sha256_init(test);
}

int main(){
  schnorr();
  //test_exponentiation_binaire(); //ok
  //free(key);
  return 0;
}
