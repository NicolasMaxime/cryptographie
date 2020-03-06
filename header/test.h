#ifndef TEST_H_
# define TEST_H_

#include "gmp.h"
#include "keygen.h"

void test_exponentiation_binaire();
void test_100_signature(mpz_t Ks, mpz_t Kp, key_gpq_t *val);

#endif /* !TEST_H_ */
