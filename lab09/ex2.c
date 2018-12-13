#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 500
#define WORD_LEN 40
#define MAX_WORDS 1000
#define FILE_NAME_LEN 128

typedef struct {
  char cuvant[WORD_LEN];
  long frecventa;
} Cuvant;

int compare_cuvinte(const void *c1, const void *c2) {
  Cuvant *cuv1 = (Cuvant *)c1;
  Cuvant *cuv2 = (Cuvant *)c2;

  if (cuv1->frecventa != cuv2->frecventa) {
    return cuv2->frecventa - cuv1->frecventa;
  }

  return strcmp(cuv1->cuvant, cuv2->cuvant);
}

void afisare_cuvinte_frecv(char *filename) {
  Cuvant cuvinte[MAX_WORDS];
  int cnt_cuvinte = 0; // nr curent de cuvinte in vectorul cuvinte[], initial 0

  FILE *fin = fopen(filename, "rt");
  if (fin == NULL) {
    printf("NU am putut deschide fisierul %s.\n", filename);
    exit(-1);
  }

  char crt[WORD_LEN];
  while (1) {
    fscanf(fin, "%s", crt);

    if (feof(fin))
      break;

    // tin toate cuvintele lowercase
    for (int i = 0; i < strlen(crt); i++)
      crt[i] = tolower(crt[i]);

    // Verific daca crt (cuv nou citit) exista deja in vectorul cuvinte[].
    // Daca da, doar ii incrementez frecventa.
    int gasit = 0;
    for (int i = 0; i < cnt_cuvinte; i++) {
      if (strcmp(cuvinte[i].cuvant, crt) == 0) {
        cuvinte[i].frecventa += 1;
        gasit = 1;
        break;
      }
    }

    // Daca nu, adaug un element nou.
    if (!gasit) {
      strcpy(cuvinte[cnt_cuvinte].cuvant, crt);
      cuvinte[cnt_cuvinte].frecventa = 1;
      cnt_cuvinte++;
    }
  }

  qsort(cuvinte, cnt_cuvinte, sizeof(Cuvant), compare_cuvinte);

  for (int i = 0; i < cnt_cuvinte; i++) {
    printf("Cuvant %s cu frecventa %ld\n", cuvinte[i].cuvant,
           cuvinte[i].frecventa);
  }
}

int main() {
  char filename[FILE_NAME_LEN];
  scanf("%s", filename); // puteti testa cu input_ex2.txt

  afisare_cuvinte_frecv(filename);
}