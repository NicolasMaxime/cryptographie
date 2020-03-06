#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"
#include "key.h"
#include "shnorr.h"

#define BASE10 10
#define NB_ESSAIE 5

/*
** Test de comparaison entre ExpMod (du DM)
** et mpz_pown (de gmp) qui calculent g^a mod p
*/

void	test_exponentiation_binaire(FILE *fp){
  mpz_t p;
  mpz_t g;
  mpz_t a;
  mpz_t ret;
  mpz_t tmp;
    
  mpz_init(p);
  mpz_init(g);
  mpz_init(a);
  mpz_init(ret);
  mpz_init(tmp);

  for (int i = 0; i != NB_ESSAIE; i++){
    make_rand_nbits(g, 60); // g number of 30 bits.
    make_rand_nbits(a, 55); // g number of 10 bits.
    make_rand_nbits(p, 34); // p number of 18 bits. 
    ExpMod(ret, g, a, p);
    mpz_powm(tmp, g, a, p);

    gmp_fprintf(fp, "g = %Zd\n", g);
    gmp_fprintf(fp, "a = %Zd\n", a);
    gmp_fprintf(fp, "p = %Zd\n\n", p);
    fprintf(fp, "g ^ a mod p : \n");
    gmp_fprintf(fp, " ->Par mpz_powm\t: %Zd\n", tmp);
    gmp_fprintf(fp, " ->Par ExpMod\t: %Zd\n\n", ret);
    
    if (!(mpz_cmp(ret, tmp) == 0)) {// ret != cmp
      fprintf(fp, "Error : ExpMod and mpz_powm don't return the same value\n");
      
    }
  }
}

void test_100_signature(mpz_t Ks, mpz_t Kp, key_gpq_t *val, FILE *fp){
  char message[10];
  int nb;
  int ret;
  int allgood;
  sign_t *signature;
  
  srand(time(NULL));
  allgood = 1;
  for (int i = 0; i != 100; i++){
    nb = rand() % 1000000000;
    sprintf(message, "%d", nb);
    message[strlen(message) + 1] = 0;
    signature = Sign(message, Ks, val);
    ret = Verify(message, signature, Kp, val);
    if (i < NB_ESSAIE){
      fprintf(fp, "message : \"%s\"\n", message);
      gmp_fprintf(fp, "Signature : (%Zd, %Zd)\n", signature->c, signature->a);
      if (ret == 0){
	fprintf(fp, "=> verification OK\n");
      }
    }
    if (ret == -1){
      fprintf(fp, "Erreur au test : %d, message : %s\n", i, message);
      allgood = 0;
    }
  }
  if (allgood){
    fprintf(fp, "Les 100 tests ont réussi\n");
  }
}
