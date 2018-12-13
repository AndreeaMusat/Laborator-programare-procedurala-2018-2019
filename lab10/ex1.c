#include <stdio.h>
#include <stdlib.h>

void citire_matrice(int n, int **mat) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void populare_fara_diagonala(int n, int **orig, int **new) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (i > j) new[i][j] = orig[i][j];
			if (i < j) new[i][j - 1] = orig[i][j];
		}
	}
}

void afisare_matrice(int linii, int coloane, int **mat) {
	for (int i = 0; i < linii; i++) {
		for (int j = 0; j < coloane; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int n;

	scanf("%d", &n);

	int **orig = (int**) malloc(n * sizeof(int*));
	int **new = (int**) malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		orig[i] = (int*) malloc(n * sizeof(int));
		new[i] = (int*) malloc((n - 1) * sizeof(int));
	}

	citire_matrice(n, orig);
	populare_fara_diagonala(n, orig, new);
	afisare_matrice(n, n - 1, new);

	for (int i = 0; i < n; i++) {
		free(orig[i]);
		free(new[i]);
	}

	free(orig);
	free(new);
}