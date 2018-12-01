#include <stdio.h>
#include <stdlib.h>

// pos si neg nu sunt matrice, ci sunt pointeri pe care vrem
// sa ii modificam in functie (deci trebuie pasati ca pointer
// la pointer, altfel nu vedem schimbarile in main)
void get_pos_neg(int n, int *arr, int *count_pos, int **pos, int *count_neg, int **neg) {
	for (int i = 0; i < n; i++) {
		arr[i] >= 0 ? (*count_pos += 1) : (*count_neg += 1);
	}

	*pos = (int*) calloc(*count_pos, sizeof(int));
	*neg = (int*) calloc(*count_neg, sizeof(int));

	int i_pos = 0, i_neg = 0;
	for (int i = 0; i < n; i++) {
		arr[i] >= 0 ? ((*pos)[i_pos++] = arr[i]) : ((*neg)[i_neg++] = arr[i]);
	}
}

void print_vector(int n, int *v) {
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);

	int *arr = (int*) calloc(n, sizeof(int));

	// deocamdata doar le declaram, alocam memorie mai tarziu
	// (atunci cand vom sti exact cate sunt cu + si cate cu -)
	int *pos, *neg; 
	int count_pos = 0, count_neg = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	get_pos_neg(n, arr, &count_pos, &pos, &count_neg, &neg);

	printf("Numerele pozitive sunt:\n");
	print_vector(count_pos, pos);
	printf("Numerele negative sunt:\n");
	print_vector(count_neg, neg);

	// Dealocam memoria (not safe fara if (arr != NULL) ... )
	free(arr);
	free(pos);
	free(neg);
}