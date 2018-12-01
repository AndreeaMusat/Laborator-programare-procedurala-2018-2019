#include <stdio.h>
#include <stdlib.h>

void print_matrix(int n, int **mat) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

void print_middle_element(int n, int **mat) {
	if (n % 2 == 0) {
		printf("There is no middle element, n is even.\n");
		return;
	}

	printf("%d \n", mat[n / 2][n / 2]);
}

void print_diagonals(int n, int **mat) {
	printf("Main diagonal:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", mat[i][i]);
	}

	printf("\nSecondary diagonal:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", mat[i][n - i - 1]);
	}

	printf("\n");
}

void swap_lines(int i, int j, int n, int **mat) {
	if (i < 0 || j < 0 || i >= n || j >= n) {
		printf("Invalid lines to swap, exiting...\n");
		return;
	}

	int aux;
	for (int k = 0; k < n; k++) {
		aux = mat[i][k];
		mat[i][k] = mat[j][k];
		mat[j][k] = aux;
	}
}

int main() {
	int n;
	scanf("%d", &n);

	// Aloc dinamic matricea mat.
	int **mat = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++) {
		mat[i] = (int*)calloc(n, sizeof(int));
	}

	// Populez matricea mat cu elemente citite de la tastatura.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &mat[i][j]);
		}
	}

	print_matrix(n, mat);
	print_middle_element(n, mat);
	print_diagonals(n, mat);
	swap_lines(0, 1, n, mat);
	printf("Matrix after swapping lines 0 and 1:\n");
	print_matrix(n, mat);

	// La final trebuie sa dealocam memoria alocata dinamic:
	for (int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);
}