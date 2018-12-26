//
// crypto methods
//


#ifndef CRYPTO_H
#define CRYPTO_H

#include "prime.h"
#include "largenumbers.h"

char *encrypt(char *msg, int key);
char *decrypt(char *msg, int key);

#endif // CRYPTO_H