#include <stdio.h>
#include <stdlib.h>

int numarare_linii_fisier(const char *filename) {
	FILE *fin = fopen(filename, "r");
	if (fin == NULL) {
		fprintf(stderr, "Nu am putut deschide fisierul %s.\n", filename);
		exit(-2);
	}

	int count_newline = 0;
	while (!feof(fin)) {
		char crt_char = fgetc(fin);
		if (crt_char == '\n') count_newline++;
	}

	fclose(fin);

	return count_newline;
}

void citire_siruri(int num_siruri, int **sequences, char *filename) {
	FILE *fin = fopen(filename, "r");
	if (fin == NULL) {
		fprintf(stderr, "Nu am putut deschide fisierul %s.\n", filename);
		exit(-2);
	}

	for (int i = 0; i < num_siruri; i++) {
		// Nr de elem din sirul curent
		int n;

		// citesc mai intai numarul de elemente din sirul curent
		fscanf(fin, "%d", &n);

		// aloc sequences[i] cu n + 1 elemente (elementul de pe poz 0 e nr de elemente)
		sequences[i] = (int*) calloc(n + 1, sizeof(int));
		sequences[i][0] = n;

		for (int j = 1; j <= n; j++) {
			fscanf(fin, "%d", &sequences[i][j]);
		}
	}
}

void afisare_siruri(int num_siruri, int **sequences) {
	for (int i = 0; i < num_siruri; i++) {
		printf("Sirul nr. %d are %d elemente: ", i, sequences[i][0]);
		for (int j = 1; j <= sequences[i][0]; j++) {
			printf("%d ", sequences[i][j]);
		}
		printf("\n");
	}
}

int seq_elem_compare(const void* elem1, const void* elem2) {
	if (*(int*)elem1 < *(int*)elem2) return -1;
	if (*(int*)elem1 > *(int*)elem2) return 1;
	return 0;

	// Sau (poate e mai usor de inteles ?)
	// int *e1 = (int*)elem1;
	// int *e2 = (int*)elem2;
	// if (*e1 != *e2) {
	// 	  return (*e1 < *e2) ? -1 : 1;
	// }
	// return 0;
}

// In mod normal, daca vrem sa comparam doua obiecte de tip Obiect, 
// in comparator trebuie sa facem cast de la void* la Obiect*
// Aici vrem sa comparam doua siruri. Cum fiecare sir e deja un vector
// (int*), trebuie sa facem cast la pointer la sir (int**)
// Comparam sirurile dupa numarul de elemente (sir[0])
int seq_compare(const void *elem1, const void *elem2) {
	int **sir1 = (int**)elem1;
	int **sir2 = (int**)elem2;

	return *sir1[0] > *sir2[0];	
}

void sortare_siruri(int num_siruri, int **sequences) {
	for (int i = 0; i < num_siruri; i++) {
		qsort(&sequences[i][1], sequences[i][0], sizeof(int), seq_elem_compare);
	}
	qsort(sequences, num_siruri, sizeof(int*), seq_compare);
}

// interclasez sirul sequences[i] si sequences[j] si sterg sequences[j]
void interclasare_siruri(int *num_siruri, int **sequences, int i, int j) {
	if (i >= *num_siruri || j >= *num_siruri) {
		fprintf(stderr, "i si j trebuie sa fie mai mici ca num_siruri\n");
		exit(-1);
	}

	// Alocam un sir temporar in care vom retine rezultatul interclasarii
	int *tmp = (int*) calloc(1 + sequences[i][0] + sequences[j][0], sizeof(int));
	tmp[0] = sequences[i][0] + sequences[j][0];

	// idx_i e indexul elementului curent din sequences[i], 
	// idx_j e indexul elementului curent din sequences[j]
	// idx_tmp e indexul elem curent din tmp
	int idx_i = 1, idx_j = 1, idx_tmp = 1;
	while (idx_i <= sequences[i][0] && idx_j <= sequences[j][0]) {
		if (sequences[i][idx_i] <= sequences[j][idx_j]) {
			tmp[idx_tmp++] = sequences[i][idx_i++]; 
		}
		else {
			tmp[idx_tmp++] = sequences[j][idx_j++];
		}
	}

	// Daca au ramas elemente in sequences[i]
	while (idx_i <= sequences[i][0]) {
		tmp[idx_tmp++] = sequences[i][idx_i++];
	}

	// Daca au ramas elemente in sequences[j]
	while (idx_j <= sequences[j][0]) {
		tmp[idx_tmp++] = sequences[j][idx_j++];
	}

	// Realoc sequences[i] ca sa poata cuprinde tmp
	sequences[i] = (int*) realloc(sequences[i], (1 + sequences[i][0] + sequences[j][0]) * sizeof(int));

	// Copiez elem din tmp in sequences[i]
	sequences[i][0] = sequences[i][0] + sequences[j][0];
	for (int k = 1; k <= sequences[i][0]; k++) {
		sequences[i][k] = tmp[k];
	}

	// Dezaloc tmp
	free(tmp);

	// Pentru stergerea lui sequences[j], il interschimb pe acesta cu ultimul sir
	// Nu dezaloc memoria acum, ci o voi dezaloca pe toata la finalul programului
	int *aux = sequences[*num_siruri - 1];
	sequences[*num_siruri - 1] = sequences[j];
	sequences[j] = aux;
	*num_siruri -= 1;
}

void interclasare_toate(int *num_siruri, int **sequences) {
	// Am num_siruri -> trebuie sa fac num_siruri - 1 interclasari ca sa 
	// ajung sa am un singur sir
	// La fiecare pas interclasez sirul 0 cu sirul 1
	int copy_num_siruri = *num_siruri;
	for (int i = 0; i < copy_num_siruri - 1; i++) {
		interclasare_siruri(num_siruri, sequences, 0, 1);
	}
}

void adaugare_sir(int *seq, char *filename) {
	FILE *fout = fopen(filename, "a");
	if (fout == NULL) {
		fprintf(stderr, "M-am plictisit sa scriu mesajul asta de eroare.\n");
		exit(-1);
	}

	fprintf(fout, "%d\n", seq[0]);
	for (int i = 1; i <= seq[0]; i++) {
		fprintf(fout, "%d ", seq[i]);
	}
	fprintf(fout, "\n");

	fclose(fout);
}

int main() {

	// Obs: siruri.txt trebuie sa aiba o linie noua dupa ultimul sir
	char filename[] = "siruri.txt";
	int num_siruri = numarare_linii_fisier(filename) / 2;
	int initial_num_siruri = num_siruri;
	printf("num_siruri = %d\n", num_siruri);
	
	// Pct a.
	int **sequences = (int**) calloc(num_siruri, sizeof(int*));
	citire_siruri(num_siruri, sequences, filename);
	
	// Pct b.
	afisare_siruri(num_siruri, sequences);
	
	// Pct c.
	sortare_siruri(num_siruri, sequences);
	printf("Sirurile dupa sortare:\n");
	afisare_siruri(num_siruri, sequences);

	// Pct d.
	// Pasez num_siruri prin adresa ca sa il pot modifica in functie (il decrementez)
	interclasare_siruri(&num_siruri, sequences, 2, 3); // interclasez sirul 0 cu sirul 2
	printf("Dupa interclasarea sirului nr 2 cu nr 3 avem:\n");
	afisare_siruri(num_siruri, sequences);

	// Pct e.
	interclasare_toate(&num_siruri, sequences);
	printf("Dupa interclasarea tuturor sirurilor obtinem:\n");
	afisare_siruri(num_siruri, sequences);

	// Pct f.
	adaugare_sir(sequences[0], filename);


	for (int i = 0; i < initial_num_siruri; i++) {
		free(sequences[i]);
	}
	free(sequences);
}