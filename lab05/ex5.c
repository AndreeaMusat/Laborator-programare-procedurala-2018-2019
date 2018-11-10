#include <stdio.h>

void print_spiral(int num_rows, int num_cols, int mat[num_rows][num_cols]) {
	int start_row = 0;
	int end_row = num_rows;
	int start_col = 0;
	int end_col = num_cols;

	while (start_row < end_row && start_col < end_col) {
		// Printam linia de sus de la stanga la dreapta (start_row)
		for (int i = start_col; i < end_col; i++) {
			printf("%d ", mat[start_row][i]);
		}
		// Am terminat de printat prima linie, incrementez contorul
		// de start al liniei.
		start_row += 1;

		// Printam coloana din dreapta de sus in jos (end_col)
		for (int i = start_row; i < end_row; i++) {
			printf("%d ", mat[i][end_col - 1]);
		}
		end_col -= 1;

		// Printam linia de jos de la dreapta la stanga
		if (start_row < end_row) {
			for (int i = end_col - 1; i >= start_col; i--) {
				printf("%d ", mat[end_row - 1][i]);
			}
			end_row -= 1;
		}

		// Printam coloana din stanga de jos in sus
		if (start_col < end_col) {
			for (int i = end_row - 1; i >= start_row; i--) {
				printf("%d ", mat[i][start_col]);
			}
			start_col += 1;
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	int mat[n][m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &mat[i][j]);
		}
	}

	print_spiral(n, m, mat);
}