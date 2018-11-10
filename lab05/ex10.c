#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
  int salt;
  int greutate;
} Cangur;

int main() {
  int N, M, sqrtN, cnt_c = 0;

  FILE *fin = fopen("mayonaka.in", "r");
  FILE *fout = fopen("mayonaka.out", "w");

  // Ugly code is ugly
  fscanf(fin, "%d %d", &N, &M);
  sqrtN = sqrt(N);

  Cangur canguri[M], c;

  long long res[N];
  long long tmp_res[N];

  memset(res, 0, sizeof(long long) * N);

  for (int i = 0; i < M; i++) {
    memset(&c, 0, sizeof(c));
    fscanf(fin, "%d %d %d %d", &c.x, &c.y, &c.salt, &c.greutate);

    c.x--, c.y--;

    // Rotunjesc c.y astfel incat sa fie ultima celula pe care chiar
    // sare un cangur.
    c.y = c.x + (c.y - c.x) / c.salt * c.salt;

    // Brute force pentru cangurii cu pas mai mare ca sqrt(N)
    // O(sqrt(N))
    if (c.salt >= sqrtN) {
      for (int i = c.x; i <= c.y; i += c.salt) {
        res[i] += c.greutate;
      }
    } else {
      canguri[cnt_c++] = c;
    }
  }

  // O(N sqrt(N))
  // Pentru pasii mai mici ca sqrtN, profitam de faptul ca cel mai
  // probabil vor fi mai multi canguri cu acelasi pas si pentru fiecare
  // cangur marcam pe un vector de rezultate temporare cu +greutate
  // pozitia x si cu -greutate pozitia y + salt, ca mai apoi sa facem
  // sume prefix pe vectorul temporar si sa updatam toate pozitiile
  // intermediare.
  for (int salt = 1; salt < sqrtN; salt++) {

    memset(tmp_res, 0, sizeof(long long) * N);

    for (int idx = 0; idx < cnt_c; idx++) {
      if (canguri[idx].salt != salt)
        continue;

      tmp_res[canguri[idx].x] += canguri[idx].greutate;
      if (canguri[idx].y + canguri[idx].salt < N)
        tmp_res[canguri[idx].y + canguri[idx].salt] -= canguri[idx].greutate;
    }

    for (int i = salt; i < N; i++) {
      tmp_res[i] += tmp_res[i - salt];
    }

    for (int i = 0; i < N; i++) {
      res[i] += tmp_res[i];
    }
  }

  for (int i = 0; i < N; i++) {
    fprintf(fout, "%lld ", res[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fclose(fout);
}