#ifndef SHNORR_H_
#define SHNORR_H_

#include "key.h"

typedef struct sign_s{
  mpz_t a;
  mpz_t c;
} sign_t; 

sign_t *Sign(char *message, mpz_t Ks,  key_gpq_t *val);
bool Verify(char *message,sign_t *signature, mpz_t Kp, key_gpq_t *val);

#endif /* !SHNORR_H_ */
