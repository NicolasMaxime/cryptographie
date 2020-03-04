#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"
#include "key.h"
#include "shnorr.h"

key_gpq_t	*generate_key(mpz_t Ks, mpz_t Kp){
  key_gpq_t	*ret;
  
  ret = keygen(256, 1792);
  key(ret, Ks, Kp);
  return ret;
}

void shnorr(char *message, mpz_t Ks, mpz_t Kp, key_gpq_t *val){
  sign_t *signature;
  
  signature = Sign(message, Ks, val);
  Verify(signature, Kp, val);
  return ;
}

int	main(){
  mpz_t Ks;
  mpz_t Kp;
  key_gpq_t *val;
  
  val = generate_key(Ks, Kp);
  shnorr("message", Ks, Kp, val);
  //test_exponentiation_binaire(); //ok
  //free(key);
  return 0;
}
