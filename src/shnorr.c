#include <stdlib.h>
#include <string.h>
#include "gmp.h"
#include "function.h"
#include "sha256.h"
#include "shnorr.h"

sign_t	*Sign(char *message, mpz_t Ks, key_gpq_t *val){
  sign_t *signature;
  mpz_t R;
  mpz_t r;
  mpz_t tmp;
  gmp_randstate_t state;

  signature = malloc(sizeof(*signature));
  mpz_init(R);
  mpz_init(r);
  mpz_init(signature->c);
  mpz_init(signature->a);
  mpz_init(tmp);
  
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, rand());
  mpz_sub_ui(tmp, val->q, 4);	// tmp = q - 4
  mpz_urandomm(r, state, tmp);// 0 <= r <= q - 4
  mpz_add_ui(r, r, 2);	// 2 <= r <= q - 2

  ExpMod(R, val->g, r, val->p); // r = g^r [p]

  /* calcul de c = H(R||M) mod q */
  TCSha256State_t sha;
  char *strR = NULL;
  char *dest;
  
  tc_sha256_init(sha);
  strR = mpz_get_str("0123456789", 10, R);
  dest = malloc(sizeof(*dest) * (strlen(strR) + strlen(message)));
  dest[0] = 0;
  strcat(dest, strR); // dest = R;
  strcat(dest, message); // dest = R || M
  
  /* Calcul de a*/
  mpz_mul(tmp, signature->c, Ks);
  mpz_sub(signature->a, r, tmp);
  mpz_set_ui(tmp, 1);
  ExpMod(signature->a, signature->a, tmp, val->q); // a^1 = r - cx [q]

  return signature;
}

/* 
*/

void Verify(sign_t *signature, mpz_t Kp, key_gpq_t *val){
  mpz_t R;
  mpz_t tmp;
  mpz_t	tmp2;
  
  mpz_init(tmp);
  mpz_init(tmp2);
  mpz_init(R);
  ExpMod(tmp, val->g, signature->a, val->p); // tmp = g^a mod p
  ExpMod(tmp2, Kp, signature->c, val->p); // tmp2 = h ^ c mod p
  mpz_mul(R, tmp, tmp2); // R = tmp * tmp2
  mpz_set_ui(tmp, 1);
  ExpMod(R, R, tmp, val->p); //  R = R[p]

  //calculer tmp = H(R || M) [q]
  //verifier c = w
  
  return;
}
