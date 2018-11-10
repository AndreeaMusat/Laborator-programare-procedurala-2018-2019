#include <stdio.h>

// Ca sa evitam alocarea dinamica, transmited matricea transpusa (nepopulata)
// ca parametru.
void compute_transpose(int n, int m, int mat[n][m], int transposed[m][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      transposed[j][i] = mat[i][j];
    }
  }
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  int mat[n][m];
  int transposed[m][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &mat[i][j]);
    }
  }

  compute_transpose(n, m, mat, transposed);

  printf("Transpusa este: \n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", transposed[i][j]);
    }
    printf("\n");
  }
}