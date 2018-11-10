#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUMS 4001

int freq_a[MAX_NUMS];
int freq_b[MAX_NUMS];

int main() {
	/* 
		Solutia de mai jos functioneaza si pentru multisets
		(Multimi in care se permit mai multe aparitii ale unui
		dingur numar)
	*/

	int n, m, x;

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		 scanf("%d", &x);
		 freq_a[x + MAX_NUMS / 2] += 1;
	}

	for (int i = 0; i < m; i++) {
		 scanf("%d", &x);
		 freq_b[x + MAX_NUMS / 2] += 1;
	}

	int count_intersection = 0;
	for (int i = 0; i <= MAX_NUMS; i++) {
		// In intersectie se afla un numar de elemente egal cu frecventa minima
		// a elementului in cele 2 multimi.
		count_intersection += (freq_a[i] < freq_b[i]) ? freq_a[i] : freq_b[i];
	}

	printf("%d\n", count_intersection);
}