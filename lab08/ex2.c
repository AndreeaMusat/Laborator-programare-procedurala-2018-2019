#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 10;
	char *p = (char *)&x;
	for (int i = 0; i <= 3; i++) {
		printf("Octetul numarul %d este %d\n", i, *(p+i));
	}
}