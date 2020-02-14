#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gmp.h"
#include "function.h"
#include "test.h"
#include "keygen.h"

int main(){
  key_gpq_t *key;

  //key = keygen(256, 1792);
  test_exponentiation_binaire(); //ok
  //free(key);
  return 0;
}
