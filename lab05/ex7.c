#include <stdio.h>

// Linia 0 devine coloana n - 1
// Linia 1 devine coloana n - 2
// ..
// Linia i devine coloana n - i - 1
void rotate(int n, int m, int mat[n][m], int rotated[m][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      rotated[j][n - i - 1] = mat[i][j];
    }
  }
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  int mat[n][m];
  int rotated[m][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &mat[i][j]);
    }
  }

  rotate(n, m, mat, rotated);

  printf("Matricea rotita este: \n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", rotated[i][j]);
    }
    printf("\n");
  }
}