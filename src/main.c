#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"
#include "key.h"
#include "shnorr.h"

key_gpq_t	*generate_key(mpz_t Ks, mpz_t Kp){
  key_gpq_t	*ret;
  
  ret = keygen(256, 1792);
  mpz_set_ui(ret->q, 7919);
  mpz_set_ui(ret->p, 63353); // k = 8;
  mpz_set_ui(ret->g, 1241);
  key(ret, Ks, Kp);
  return ret;
}

void	 shnorr(char *message, mpz_t Ks, mpz_t Kp, key_gpq_t *val, FILE *fp){
  sign_t *signature;
  int ret;
  
  signature = Sign(message, Ks, val);
  gmp_fprintf(fp, "q : 7919\np : 63353\ng : 1241\n\n");
  gmp_fprintf(fp, "message : \"%s\"\nSignature généré : (%Zd, %Zd)\n", message, signature->c, signature->a);
  ret = Verify(message, signature, Kp, val);
  if (ret == 0){
    gmp_fprintf(fp, "==>Signature vérifiée\n");
  }
  else {
    fprintf(fp, "==>signature invalide\n");
  }
  gmp_fprintf(fp, "\nTest de la même signature sur un message bidon :\n");
  fprintf(fp, "message : \"<Ceci est un nouveau message>\"\n");
  fprintf(fp, "La signature ne change pas\n");
  ret = Verify("<Ceci est un nouveau message>", signature, Kp, val);
  if (ret == 0)
    gmp_fprintf(fp, "=>Signature vérifiée\n");
  else
    fprintf(fp, "=>signature invalide\n");
}

int	main(int ac, char av){
  mpz_t Ks;
  mpz_t Kp;
  key_gpq_t *val;
  FILE *fp;

  fp = fopen("./test.txt", "w");
  fprintf(fp, "<============ TEST EXPMOD ==================>\n");
  test_exponentiation_binaire(fp);
  fprintf(fp, "\n<=========== Generation clé ================>\n");
  val = generate_key(Ks, Kp);
  fprintf(fp, "\n<=========== Test de la signature de shnorr sur un exemple ==========>\n");
  shnorr("Parce que l'on a pas reussi a generer des clefs, on en a mise par defaut avec des petits nombre premiers", Ks, Kp, val, fp);
  fprintf(fp, "\n<=========== Test des 100 signature et vérification : ======================>\n");
  test_100_signature(Ks, Kp, val, fp);
  fclose(fp);
  return 0;
}
