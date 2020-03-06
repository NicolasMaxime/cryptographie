#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

  ExpMod(R, val->g, r, val->p); // R = g^r [p]

  /* calcul de H(R||M) */
  TCSha256State_t sha;
  uint8_t digest[32];
  char *strR = NULL;
  char *dest;
 
  strR = mpz_get_str(NULL, 10, R);
  dest = malloc(sizeof(*dest) * (strlen(strR) + strlen(message)) + 1);
  dest[0] = 0;
  strcat(dest, strR); // dest = R;
  strcat(dest, message); // dest = R || M
  sha = malloc(sizeof(*sha));
  tc_sha256_init(sha);
  tc_sha256_update(sha,(const uint8_t *)dest,strlen(strR) + strlen(message)); // H(R||M)
  tc_sha256_final(digest, sha);

  /* Transformation du haché en nombre */
  char *convert = malloc(32 * 3 * sizeof(char) + 1);
  convert[0] = 0;
  char stock[3];
  for (int i = 0; i != 32; i++){
    stock[0] = 0;
    sprintf(stock, "%d", digest[i]);
    strcat(convert, stock);
  }

  /* Calcul de c */
  mpz_set_str(tmp, convert, 10);
  mpz_mod(signature->c,tmp,val->q);// modulo q
  
  /* Calcul de a*/
  mpz_mul(tmp, signature->c, Ks);
  mpz_sub(signature->a, r, tmp);
  mpz_mod(signature->a, signature->a, val->q); // a = r - cx [q]

  free(sha);
  free(dest);
  free(convert);
  return signature;

}


int	Verify(char* message, sign_t *signature, mpz_t Kp, key_gpq_t *val){
  mpz_t R;
  mpz_t tmp;
  mpz_t	tmp2;
  
  mpz_init(tmp);
  mpz_init(tmp2);
  mpz_init(R);

  /* Calcul de R' = g^a * h^c mod p */
  ExpMod(tmp, val->g, signature->a, val->p); // tmp = g^a mod p
  ExpMod(tmp2, Kp, signature->c, val->p); // tmp2 = h ^ c mod p
  mpz_mul(R, tmp, tmp2); // R = tmp * tmp2
  mpz_mod(R, R, val->p); //  R = R[p]

  /* calcule de H(R'|| M) [q] */
  TCSha256State_t sha;
  uint8_t digest[32];
  char *strR = NULL;
  char *dest = NULL;

  strR = mpz_get_str(NULL, 10, R);
  dest = malloc(sizeof(*dest) * (strlen(strR) + strlen(message)) +1);
  dest[0] = 0;
  strcat(dest, strR); // dest = R;
  strcat(dest, message); // dest = R || M
  
  sha = malloc(sizeof(*sha));
  tc_sha256_init(sha);
  tc_sha256_update(sha,(const uint8_t *)dest,strlen(strR) + strlen(message)); // H(R||M)
  tc_sha256_final(digest, sha);

  char *convert = malloc(32 * 3 * sizeof(char) + 1);
  convert[0] = 0;
  char stock[3];
  for (int i = 0; i != 32; i++){
    stock[0] = 0;
    sprintf(stock, "%d", digest[i]);
    strcat(convert, stock);
  }
  mpz_set_str(tmp, convert, 10);
  mpz_mod(tmp,tmp,val->q);// modulo
  
  free(sha);
  free(dest);
  free(convert);
  
//verifier c = w
  if(mpz_cmp(tmp, signature->c) == 0){
    return 0;
  }
  return -1;
}
