//
// crypto methods
//


#ifndef CRYPTO_H
#define CRYPTO_H

//
// primality test methods
//


#ifndef PRIME_H
#define PRIME_H

//
// compute methods
//

#ifndef MYMATH_H
#define MYMATH_H

//
// primality test methods
//



int sum(int a[], int size);
int messageLength(char *msg);

#endif // MYMATH_H
int isPrime(int n);

#endif // PRIME_H

//
// large numbers
//


struct LargeNumber {
	int numberOfDigits;
	int *digits;
};

void add(struct LargeNumber *number1, struct LargeNumber *number2);
void mul(struct LargeNumber *number1, struct LargeNumber *number2);
void sub(struct LargeNumber *number1, struct LargeNumber *number2);

char *encrypt(char *msg, int key);
char *decrypt(char *msg, int key);

#endif // CRYPTO_H
int main() {
   encrypt("code over multiple files", 23);
   return 0;
}