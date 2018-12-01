#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void get_max_elem_pos(int n, int arr[], int *cnt_max_elem, int **max_elem_pos) {
	int max_elem = INT_MIN;		// valoarea elementului maxim din arr
	int max_elem_idx = -1;		// indexul primei aparitii a elementului maxim in arr
	
	// Determinam maximul din arr.
	for (int i = 0; i < n; i++) {
		if (arr[i] > max_elem) {
			max_elem = arr[i];
			max_elem_idx = i;
		}
	}

	// Numaram cate elem sunt egale cu maximul.
	for (int i = 0; i < n; i++) {
		*cnt_max_elem += (arr[i] == max_elem) ? 1 : 0;
	}

	// aloc dinamic max_elem_pos
	*max_elem_pos = (int*) calloc(*cnt_max_elem, sizeof(int));

	// Populez max_elem_pos cu pozitiile la care se gasesc elem maxime.
	int cnt = 0;    // cnt = cate elemente are max_elem_pos 
	for (int i = 0; i < n; i++) {
		if (arr[i] == max_elem) {
			(*max_elem_pos)[cnt++] = i;
		}
	}
}

void print_vector(int n, int *v) {
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main() {
	int arr[] = {3, 5, 1, 100, 0, 2, 100, 0, 32, 100, 100, 0, 2, 3, -3, -1};
	int n = sizeof(arr) / sizeof(int);

	int *max_elem_pos;	   // vectorul in care vom retine indecsii elementelor max din arr
	int cnt_max_elem = 0;  // nr de elemente egale cu elem max din arr
	get_max_elem_pos(n, arr, &cnt_max_elem, &max_elem_pos);

	printf("Pozitiile la care apare elementul maxim in arr sunt:\n");
	print_vector(cnt_max_elem, max_elem_pos);

	// Dealoc memoria alocata dinamic
	free(max_elem_pos);
}