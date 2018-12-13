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

void afisare_matrice(int N, int **mat) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

// Inmultim o matrice inferior triunghiulara cu una superior triunghiulara
int** inmultire_inf_sup(int N, int **inf, int **sup) {
	int **result = (int**) calloc(N, sizeof(int*));
	for (int i = 0; i < N; i++) {
		result[i] = (int*) calloc(N, sizeof(int));
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				// In mod normal aici inmultesc inf[i][k] cu sup[k][j]
				// si adun la result[i][j].
				// Pentru ca inf e inferior triunghiulara, elementul inf[i][j]
				// exista doar daca k <= i
				// Pentru ca sup e superior triunghiulara, elementul sup[k][j]
				// exista doar daca j >= k
				if (k <= i && j >= k) {
					// Pentru ca nu am stocat zero-urile din sup (si deci 
					// primul element de pe fiecare linie este elementul de pe 
					// diagonala principala, care va fi pe pozitia 0), trebuie 
					// sa scad k din indexul coloanei lui sup.
					result[i][j] += inf[i][k] * sup[k][j - k];
				}
			}
		}
	}

	return result;
}

int main() {
	int N, M;
	int **inf = citire_matrice_inf_triunghiulara("matrice_inf.txt", &N);
	int **sup = citire_matrice_sup_triunghiulara("matrice_sup.txt", &M);

	if (N != M) {
		fprintf(stderr, "Matricele nu pot fi inmultite.\n");

		// Urmeaza sa ies din program, deci dezaloc memoria aici
		for (int i = 0; i < N; i++) {
			free(inf[i]);
		}
		for (int i = 0; i < M; i++) {
			free(sup[i]);
		}
		free(inf);
		free(sup);

		exit(-1);
	}

	int **res = inmultire_inf_sup(N, inf, sup);

	afisare_matrice(N, res);

	// dezalocare memorie
	for (int i = 0; i < N; i++) {
		free(inf[i]);
		free(sup[i]);
		free(res[i]);
	}

	free(inf);
	free(sup);
	free(res);
}
