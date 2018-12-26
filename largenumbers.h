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
