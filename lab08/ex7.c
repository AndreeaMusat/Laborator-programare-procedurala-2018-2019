#include <stdio.h>
#include <stdlib.h>

void print_vector(int n, double *v) {
	for (int i = 0; i < n; i++) {
		printf("%.2lf ", v[i]);
	}
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);

	int *arr_orig = (int*) malloc(sizeof(int) * n);
	double *arr_mean = (double*) malloc(sizeof(double) * (2 * n - 1));  // De ce 2 * n - 1?

	for (int i = 0; i < n; i++) {
		scanf("%d ", &arr_orig[i]);
	}

	for (int i = 0; i < n - 1; i++) {
		arr_mean[2 * i] = arr_orig[i];
		arr_mean[2 * i + 1] = (arr_orig[i] + arr_orig[i + 1]) / 2.0;   // De ce 2.0 ?
	}
	arr_mean[2 * (n - 1)] = arr_orig[n - 1];

	printf("Vectorul nou este:\n");
	print_vector(2 * n - 1, arr_mean);

	free(arr_orig);
	free(arr_mean);
}