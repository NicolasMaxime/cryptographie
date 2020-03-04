#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gmp.h"
#include "function.h"
#include "key.h"

/*
**  Key(); 
**
*/
static unsigned long int seed = 1;

void key(key_gpq_t *key, mpz_t Kp, mpz_t Ks) {
    //Cacul d'un nombre aléatoire x entre 2 et p-2 (Ks)
    mpz_t x;
    mpz_init(x);
    mpz_t tmp;
    mpz_init(tmp);
    
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed *rand());
    seed += 1;
    
    mpz_sub_ui(tmp, key->p, 4);	// tmp = p - 4
    mpz_urandomm(x, state, tmp);// 0 <= g <= p - 4
    mpz_add_ui(x, x, 2);	// 2 <= g <= p - 2
    
    mpz_init(Ks);
    mpz_set(Ks, x);
    
    //Calcul de h = g^x(mod p) (Kp)
    mpz_t h;
    mpz_init(h);
    mpz_powm(h, key->g, x, key->p);
    
    mpz_init(Kp);
    mpz_set(Kp, h);
}
