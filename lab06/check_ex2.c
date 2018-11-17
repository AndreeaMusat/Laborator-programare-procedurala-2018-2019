#include <stdio.h>
#include <stdlib.h>

void read_and_print_file(const char *file_name) {
  int x;

  // Deschid fisierul in modul citire binar.
  FILE *f = fopen(file_name, "rb");
  if (f == NULL) {
    fprintf(stderr, "Fisierul %s nu a putut fi deschis.\n", file_name);
    exit(-1);
  }

  printf("Continutul fisierului %s este:\n", file_name);

  // Citesc intregi din fisier cat timp numarul de elemente citite cu
  // succes de fread nu este 0.
  while (1) {
    size_t succ_read = fread(&x, sizeof(int), 1, f);
    if (succ_read == 0)
      break;

    // Afisez intregul citit.
    printf("%d ", x);
  }

  printf("\n");
}

int main() {
  read_and_print_file("numere_pozitive.bin");
  read_and_print_file("numere_negative.bin");

  return 0;
}