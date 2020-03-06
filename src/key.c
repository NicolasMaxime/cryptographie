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

void key(key_gpq_t *key, mpz_t Ks, mpz_t Kp) {
    //Cacul d'un nombre aléatoire entre 2 et p-2 (Ks)
    mpz_t tmp;
    gmp_randstate_t state;
    
    mpz_init(tmp);
    mpz_init(Ks);
    
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed *rand());
    seed += 1;
    
    mpz_sub_ui(tmp, key->p, 4);	// tmp = p - 4
    mpz_urandomm(Ks, state, tmp);// 0 <= x <= p - 4
    mpz_add_ui(Ks, Ks, 2);	// 2 <= x <= p - 2
    
    //Calcul de h = g^x(mod p) (Kp)
    mpz_init(Kp);
    ExpMod(Kp, key->g, Ks, key->p);
}
