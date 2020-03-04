#include "gmp.h"
#include "function.h"
#include "sha256.h"

void Sign(char *message, mpz_t Ks){
  return;
}

void Verify(mpz_t c, mpz_t a, mpz_t g, mpz_t h, mpz_t p){
  mpz_t R;
  mpz_t tmp;
  mpz_t	tmp2;
  
  mpz_init(tmp);
  mpz_init(tmp2);
  mpz_init(R);
  ExpMod(tmp, g, a, p); // tmp = g^a mod p
  ExpMod(tmp2, h, c, p); // tmp2 = h ^ c mod p
  mpz_mul(R, tmp, tmp2); // R = tmp * tmp2
  mpz_set_ui(tmp, 1);
  ExpMod(R, R, tmp, p); //  R = R[p]

  //calculer tmp = H(R || M) [q]
  //verifier c = w
  
  return;
}
