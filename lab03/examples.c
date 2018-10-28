#include <ctype.h>
#include <stdio.h>

#include "examples.h"

#define MY_MAGIC_NUMBER 0xdeadbeef
// #define DEBUG  // echivalent cu copilare cu -DDEBUG in linia de comanda

int main() {
  char c;

  // Exemplu 1
  while (1)
  {
  	c = getchar();

  	// Pe unix, EOF in linia de comanda este ctrl + D
  	if (c != EOF)
  	{
  		if (c >= 'A' && c <= 'Z')
  		{
  			c = tolower(c);
  		}

  		putchar(c);
  	}

  	else break;
  }

  // Ex 2
  float n = 2 * PI * PI;
#undef PI // il uitam pe PI

  printf("%f\n", n);
  printf("%d\n", MY_MAGIC_NUMBER);
  printf("%d\n", PRODUS(1 + 2, 3 + 2));

// Compilare conditionata.
#ifdef DEBUG
  printf("This is a message you should not see\n");
#endif

  int x = 23, y = 456;
  printf("Before swap: x = %d, y = %d\n", x, y);
  SWAP_INPLACE(x, y);
  printf("After swap: x = %d, y = %d\n", x, y);

  struct Elev elev1;
  return 0;
}
