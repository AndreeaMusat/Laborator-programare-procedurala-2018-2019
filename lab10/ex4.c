#include <stdio.h>
#include <stdlib.h>

int** citire_matrice_inf_triunghiulara(char *filename, int *N) {
	FILE *fin = fopen(filename, "rt");
	if (fin == NULL) {
		fprintf(stderr, "Nu am putut deschide fisierul %s pentru citire\n", filename);
		exit(-1);
	}

	// Citesc dimensiunea matricei
	fscanf(fin, "%d", N);

	// Aloc si citesc matricea din fisier
	int **mat = (int**) malloc(*N * sizeof(int*));
	for (int i = 0; i < *N; i++) {
		mat[i] = (int*) malloc((i + 1) * sizeof(int));
		for (int j = 0; j <= i; j++) {
			fscanf(fin, "%d", &mat[i][j]);
		}
	}

	// Returnez matricea
	return mat;
}

void afisare_matrice_inf_triunghiulara(int N, int **mat) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int main() {
	char filename[] = "matrice_inf.txt";
	int N; // dimensiunea matricei - o vom citi din fisier
	int **mat = citire_matrice_inf_triunghiulara(filename, &N);

	afisare_matrice_inf_triunghiulara(N, mat);

	// Dezalocare mat 
	for (int i = 0; i < N; i++) {
		free(mat[i]);
	}
	free(mat);
}