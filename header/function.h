#ifndef FUNCTION_H_
# define FUNCTION_H_

#include "gmp.h"

void	ExpMod(mpz_t ret, mpz_t g, mpz_t a, mpz_t p); // set ret as g^a mod p

#endif /* !FUNCTION_H_ */
