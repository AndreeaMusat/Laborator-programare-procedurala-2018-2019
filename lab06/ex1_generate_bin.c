#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX_DIM = 1024;

int main() {
  // Generez aleator m numere intre [-n si n]
  int n, m, i, r;
  int random_nums[MAX_DIM];

  // Citesc n (pentru intervalul in care generez numerele random) si m (numarul
  // de elemente)
  scanf("%d %d", &n, &m);

  // Seteaza seed-ul pentru generatorul de numere random (poate fi omis)
  srand(time(NULL));

  // Generez m numere aleatoare intre -n si n
  for (i = 0; i < m; i++) {
    // Aleg semnul astfel:
    // generez un numar random intre 0 si 1 (rand() e intre 0 si RAND_MAX,
    // deci rand() / RAND_MAX (cu cast la float) va fi intre 0 si 1).
    // Pentru ca vrem probabilitati egale ca numarul sa fie negativ sau
    // pozitiv, daca numarul astfel generat e < 0.5, atunci semnul va fi +,
    // altfel semnul va fi -
    int sign = (((float)rand() / (float)(RAND_MAX)) <= 0.5 ? 1 : -1);

    // Generez un numar random si fac modulo (n + 1) pentru a ma
    // asigura ca rezultatul nu depaseste n. In plus, inmultesc cu semnul.
    random_nums[i] = (int)(sign * (rand() % (n + 1)));
  }

  // Deschid fisierul binar in modul citire. (Daca nu exista fisierul,
  // este creat. Daca exista, i se sterge continutul).
  FILE *fin = fopen("random.bin", "wb");
  if (fin == NULL) {
    printf("Fisierul nu a putut fi deschis.\n");
    return -1;
  }

  // Scriu numarul de elemente din vector si apoi elementele.
  fwrite(&m, sizeof(int), 1, fin);
  fwrite(random_nums, sizeof(int), m, fin);

  // Inchid fisierul binar.
  fclose(fin);

  return 0;
}