#include <stdio.h>
#include <stdlib.h>

int** citire_matrice_sup_triunghiulara(char *filename, int *N) {
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
		mat[i] = (int*) malloc((*N - i) * sizeof(int));
		for (int j = 0; j < *N - i; j++) {
			fscanf(fin, "%d", &mat[i][j]);
		}
	}

	// Returnez matricea
	return mat;
}

void afisare_matrice_sup_triunghiulara(int N, int **mat) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int main() {
	char filename[] = "matrice_sup.txt";
	int N; // dimensiunea matricei - o vom citi din fisier
	int **mat = citire_matrice_sup_triunghiulara(filename, &N);

	// Matrice superior triunghiulara arata asa:
	// X X X X X
	// O X X X X
	// O O X X X
	// O O O X X
	// O O O O X
	// unde X reprezinta elementele si O zerourile
	// Ca sa salvam memorie, pe linia i stocam N - i elemente
	afisare_matrice_sup_triunghiulara(N, mat);

	// Dezalocare mat 
	for (int i = 0; i < N; i++) {
		free(mat[i]);
	}
	free(mat);
}