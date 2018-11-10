#include <limits.h>
#include <stdio.h>
#include <string.h>

// Functia strip primeste o matrice n x m si calculeaza submat obtinuta
// prin eliminarea liniei i si a coloanei j din mat.
int strip(int n, int m, int mat[n][m], int i, int j, int submat[n - 1][m - 1]) {
  for (int idx1 = 0; idx1 < n; idx1++) {
    for (int idx2 = 0; idx2 < m; idx2++) {
      if (idx1 == i || idx2 == j)
        continue;

      int submat_idx1 = ((idx1 < i) ? idx1 : idx1 - 1);
      int submat_idx2 = ((idx2 < j) ? idx2 : idx2 - 1);

      submat[submat_idx1][submat_idx2] = mat[idx1][idx2];
    }
  }
}

int determinant(int n, int m, int mat[n][m]) {
  // Returnam INT_MIN daca matricea nu e patratica.
  if (n != m)
    return INT_MIN;

  if (n == 2) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
  }

  int submat[n - 1][m - 1];
  memset(submat, 0, (n - 1) * (m - 1) * sizeof(int));

  // Descompunem dupa prima linie
  int result = 0;
  for (int j = 0; j < m; j++) {
    strip(n, m, mat, 0, j, submat);

    int d = mat[0][j] * determinant(n - 1, m - 1, submat);
    if (j % 2 == 1)
      d *= (-1);

    result += d;
  }

  return result;
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

  int det = determinant(n, m, mat);
  printf("%d\n", det);
}