#include <stdio.h>
#include <string.h>

// Daca x e prim, returnam -1.
// Altfel, returnam cel mai mic divizor propriu al lui x.
// Presupunem ca x va fi intotdeauna mai mare sau egal cu 2.
int prime_or_smallest_divisor(int x) {
  if (x == 1 || x == 2)
    return -1;

  for (int d = 2; d * d <= x; d++) {
    if (x % d == 0) {
      return d;
    }
  }

  return -1;
}

void fill_nums(int N, int nums[]) {
  memset(nums, 0, sizeof(int) * N);

  int prev = 2, prev_prev = 1;
  nums[0] = prev_prev;
  nums[1] = prev;

  // Completam nums[] astfel:
  // Daca elementul prev_prev (cu 2 elemente inainte de cel curent)
  // nu a fost prim, atunci elem curent e acela + 1
  // Altfel, daca a fost prim, atunci ma uit la elementul prev
  // si daca si acesta a fost prim, elem curent va fi prev + 1
  // Altfel, e primul divizor al lui prev.
  for (int i = 2; i < N; i++) {
    int prime_or_div_prev_prev = prime_or_smallest_divisor(prev_prev);
    if (prime_or_div_prev_prev != -1) {
      nums[i] = prev_prev + 1;
    } else {
      int prime_or_div_prev = prime_or_smallest_divisor(prev);
      if (prime_or_div_prev != -1) {
        nums[i] = prime_or_div_prev;
      } else {
        nums[i] = prev + 1;
      }
    }

    // Updatez prev_prev si prev pentru iteratia urmatoare.
    prev_prev = prev;
    prev = nums[i];
  }
}

void fill_in_spiral(int num_rows, int num_cols, int mat[num_rows][num_cols],
                    int nums[]) {
  int start_row = 0;
  int end_row = num_rows;
  int start_col = 0;
  int end_col = num_cols;
  int cnt = 0;

  while (start_row < end_row && start_col < end_col) {
    // Printam linia de sus de la stanga la dreapta (start_row)
    for (int i = start_col; i < end_col; i++) {
      mat[start_row][i] = nums[cnt++];
    }
    // Am terminat de printat prima linie, incrementez contorul
    // de start al liniei.
    start_row += 1;

    // Printam coloana din dreapta de sus in jos (end_col)
    for (int i = start_row; i < end_row; i++) {
      mat[i][end_col - 1] = nums[cnt++];
    }
    end_col -= 1;

    // Printam linia de jos de la dreapta la stanga
    if (start_row < end_row) {
      for (int i = end_col - 1; i >= start_col; i--) {
        mat[end_row - 1][i] = nums[cnt++];
      }
      end_row -= 1;
    }

    // Printam coloana din stanga de jos in sus
    if (start_col < end_col) {
      for (int i = end_row - 1; i >= start_row; i--) {
        mat[i][start_col] = nums[cnt++];
      }
      start_col += 1;
    }
  }
}

int main() {
  // nr linii, nr de coloane.
  int n, m;
  scanf("%d %d", &n, &m);
  int mat[n][m];
  int nums[n * m];

  // Mai intai determinam numerele cu care trebuie populata in spirala
  // matricea, apoi o populam efectiv (Putem totusi sa salvam memorie
  // si sa nu mai memoram nums, ci sa le generam pe masura ce completam
  // matricea, insa este mai usor de urmarit codul asa)
  fill_nums(n * m, nums);
  fill_in_spiral(n, m, mat, nums);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%3d ", mat[i][j]);
    }
    printf("\n");
  }
}