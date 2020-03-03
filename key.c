#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gmp.h"
#include "function.h"

/*
**  Key(); 
**
*/

void key(mpz_t q, mpz_t p, mpz_t g, mpz_t Kp, mpz_t Ks) {
    //Cacul d'un nombre aléatoire x entre 2 et p-2 (Ks)
    mpz_t x;
    mpz_init(x);
    mpz_init(tmp);
    mpz_sub_ui(tmp, p, 4);	// tmp = p - 4
    mpz_urandomm(x, state, tmp);// 0 <= g <= p - 4
    mpz_add_ui(x, x, 2);	// 2 <= g <= p - 2
    
    mpz_init(Ks);
    mpz_set(Ks, x);
    
    //Calcul de h = g^x(mod p) (Kp)
    mpz_t h;
    mpz_init(h);
    mpz_pow(tmp, g, x);
    mpz_mod(h, tmp, p);
    
    mpz_init(Kp);
    mpz_set(Kp, h);
}
