#ifndef SHNORR_H_
#define SHNORR_H_

void Sign(char *message, mpz_t Ks);
void Verify(mpz_t c, mpz_t a, mpz_t g, mpz_t h, mpz_t p);

#endif /* !SHNORR_H_ */
