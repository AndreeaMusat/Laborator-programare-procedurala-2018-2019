#include <stdio.h>
#include <stdlib.h>

int main() {
	int n;
	scanf("%d", &n);

	int **mat = (int**) calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++) {
		mat[i] = (int*) calloc(i + 1, sizeof(int));
	}

	// Populez prima coloana si ultima linie
	for (int i = 0; i < n; i++) {
		mat[i][0] = n - i;
		mat[n - 1][i] = i + 1;
	}

	// Populez restul folosind valorile din Sud si Vest
	for (int i = n - 2; i >= 1; i--) {
		for (int j = 1; j <= i; j++) {
			mat[i][j] = mat[i][j - 1] + mat[i + 1][j];
		}
	}

	// Afisez matricea
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}

	// Dezalocare memorie
	for (int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);
}