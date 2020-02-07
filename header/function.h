#ifndef FUNCTION_H_
# define FUNCTION_H_

#include "gmp.h"

void	ExpMod(mpz_t ret, mpz_t p, mpz_t g, mpz_t a); // return A with A = g^a mod p

#endif /* !FUNCTION_H_ */
