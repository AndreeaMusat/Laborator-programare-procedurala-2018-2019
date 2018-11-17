#include <stdio.h>

int main() {

  // n = Numarul de numere ce vor fi citite din numere_intregi.txt
  int n, x;

  // Deschid fisierul numere_intregi.txt in modul citire text.
  FILE *fin = fopen("numere_intregi.txt", "rt");

  // Deschid fisierele 'numere_pozitive.bin' si 'numere_negative.bin'
  // in modul de scriere fisier binar.
  FILE *f_pos = fopen("numere_pozitive.bin", "wb");
  FILE *f_neg = fopen("numere_negative.bin", "wb");

  // Error handling
  if (fin == NULL || f_pos == NULL || f_neg == NULL) {
    printf("Un fisier nu a putut fi deschis.\n");
    return -1;
  }

  // Citesc numarul de intregi ce urmeaza in fisier (n)
  fscanf(fin, "%d", &n);

  // Citesc cei n intregi
  for (int i = 0; i < n; i++) {
    fscanf(fin, "%d", &x);

    // Daca numarul citit x este < 0, scriu numarul in f_neg,
    // altfel in f_pos
    fwrite(&x, sizeof(int), 1, (x < 0 ? f_neg : f_pos));
  }

  // Inchid toate fisierele
  fclose(fin);
  fclose(f_pos);
  fclose(f_neg);

  return 0;
}