#include <stdio.h>
#include <stdlib.h>

const int MAX_DIM = 1024;

int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {

  int cnt, i;
  int random_nums[MAX_DIM];

  // Deschid fisierul binar in modul citire. (Daca nu exista, va intoarce
  // NULL si programul va returna -1)
  FILE *fin = fopen("random.bin", "rb");
  if (fin == NULL) {
    printf("Fisierul nu a putut si deschis.\n");
    return -1;
  }

  // Citesc mai intai un intreg din fisier (numarul de elemente ce trebuie
  // citite)
  fread(&cnt, sizeof(int), 1, fin);

  // Citesc vectorul de elemente generate random folosind ex1_generate_bin.c
  fread(random_nums, sizeof(int), cnt, fin);

  // Sortez numerele citite
  qsort(random_nums, cnt, sizeof(int), cmpfunc);

  // Valoarea maxima este acum ultimul element.
  int max_val = random_nums[cnt - 1];

  // Numar cate elemente sunt egale cu elementul cu valoare maxima.
  // (Pentru ca vectorul era sortat, puteam porni cu for-ul de la final
  // catre inceput, iar cand elementul curent nu mai era egal cu valoarea
  // maxima, break)
  int count_max_val = 0;
  for (i = 0; i < cnt; i++) {
    if (random_nums[i] == max_val) {
      count_max_val += 1;
    }
  }

  printf("Valoarea maxima este %d si apare de %d ori in fisier.\n", max_val,
         count_max_val);
  printf("Valorile citite sunt:\n");

  for (int i = 0; i < cnt; i++) {
    printf("%d ", random_nums[i]);
  }
  printf("\n");

  return 0;
}