#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_CNP 13
#define LEN_NUME 30

typedef struct {
  char *nume;
  char cnp[LEN_CNP];
  int varsta;
  double salariu;
} Angajat;

void exit_message(int code, char message[]) {
  printf("message\n");
  exit(code);
}

// citesc num_angajati de la tastatura si apoi angajatii pe rand
void scrie_angajati_bin() {
  Angajat ang;
  ang.nume = (char *)malloc(LEN_NUME * sizeof(char));

  FILE *fout = fopen("angajati.bin", "wb");
  if (fout == NULL) {
    exit_message(-1, "Nu am putut crea fisierul binar");
  }

  int num_angajati;
  scanf("%d", &num_angajati);

  for (int i = 0; i < num_angajati; i++) {
    scanf("%s %s %d %lf", ang.nume, ang.cnp, &ang.varsta, &ang.salariu);
    fwrite(ang.nume, sizeof(char), LEN_NUME, fout);
    fwrite(ang.cnp, sizeof(char), LEN_CNP, fout);
    fwrite(&ang.varsta, sizeof(int), 1, fout);
    fwrite(&ang.salariu, sizeof(double), 1, fout);
    fflush(fout);
  }

  fclose(fout);
  free(ang.nume);
}

void afisare_dupa_cnp(char cnp[LEN_CNP]) {
  Angajat ang;
  ang.nume = (char *)malloc(LEN_NUME * sizeof(char));

  FILE *fin = fopen("angajati.bin", "rb");
  if (fin == NULL) {
    exit_message(-1, "Nu am putut deschide fisierul binar");
  }

  int gasit = 0;
  while (1) {
    int succes = fread(ang.nume, sizeof(char), LEN_NUME, fin);
    if (succes == 0)
      break;

    fread(ang.cnp, sizeof(char), LEN_CNP, fin);
    fread(&ang.varsta, sizeof(int), 1, fin);
    fread(&ang.salariu, sizeof(double), 1, fin);

    if (strcmp(ang.cnp, cnp) == 0) {
      gasit = 1;
      printf("Angajatul cu CNP-ul %s este: %s, %d ani, salariu %lf\n", cnp,
             ang.nume, ang.varsta, ang.salariu);
      break;
    }
  }

  fclose(fin);

  if (!gasit) {
    printf("Nu am gasit angajatul cu CNP-ul %s\n", cnp);
  }

  free(ang.nume);
}

void adaugare_angajat() {
  Angajat ang;
  ang.nume = (char *)malloc(LEN_NUME * sizeof(char));

  FILE *fout = fopen("angajati.bin", "ab");
  if (fout == NULL) {
    exit_message(-1,
                 "Nu am putut deschide fisierul binar pentru adaugare angajat");
  }

  scanf("%s %s %d %lf", ang.nume, ang.cnp, &ang.varsta, &ang.salariu);
  fwrite(ang.nume, sizeof(char), LEN_NUME, fout);
  fwrite(ang.cnp, sizeof(char), LEN_CNP, fout);
  fwrite(&ang.varsta, sizeof(int), 1, fout);
  fwrite(&ang.salariu, sizeof(double), 1, fout);
  fflush(fout);
  fclose(fout);
  free(ang.nume);
}

void scriere_angajati_txt() {
  Angajat ang;
  ang.nume = (char *)malloc(LEN_NUME * sizeof(char));

  FILE *fin = fopen("angajati.bin", "rb");
  FILE *fout = fopen("salarii.txt", "wt");
  if (fin == NULL || fout == NULL) {
    exit_message(-1,
                 "Nu am putut deschide unul dintre fisiere pentru scriere txt");
  }

  double total_salarii = 0.0;
  int num_angajati = 0;
  while (1) {
    int succes = fread(ang.nume, sizeof(char), LEN_NUME, fin);
    if (succes == 0)
      break;

    fread(ang.cnp, sizeof(char), LEN_CNP, fin);
    fread(&ang.varsta, sizeof(int), 1, fin);
    fread(&ang.salariu, sizeof(double), 1, fin);

    total_salarii += ang.salariu;
    num_angajati += 1;

    fprintf(fout, "%s %lf\n", ang.nume, ang.salariu);
    fflush(fout);
  }

  fprintf(fout, "Salariu mediu: %lf\n", total_salarii / num_angajati);
  fclose(fin);
  fclose(fout);
  free(ang.nume);
}

void afisare_angajati_salariu_maxim() {
  FILE *fin = fopen("angajati.bin", "rb");
  if (fin == NULL) {
    exit_message(-1, "Nu am putut deschide angajati.bin pentru citire");
  }

  Angajat ang;
  ang.nume = (char *)malloc(LEN_NUME * sizeof(char));

  double salariu_maxim = 0;

  // citesc fisierul si determin salariul maxim
  while (1) {
    int succes = fread(ang.nume, sizeof(char), LEN_NUME, fin);
    if (succes == 0)
      break;

    fread(ang.cnp, sizeof(char), LEN_CNP, fin);
    fread(&ang.varsta, sizeof(int), 1, fin);
    fread(&ang.salariu, sizeof(double), 1, fin);

    if (ang.salariu > salariu_maxim) {
      salariu_maxim = ang.salariu;
    }
  }

  // mut cursorul la inceput din nou
  fseek(fin, 0, SEEK_SET);

  // citesc iar fisierul
  while (1) {
    int succes = fread(ang.nume, sizeof(char), LEN_NUME, fin);
    if (succes == 0)
      break;

    fread(ang.cnp, sizeof(char), LEN_CNP, fin);
    fread(&ang.varsta, sizeof(int), 1, fin);
    fread(&ang.salariu, sizeof(double), 1, fin);

    if (ang.salariu == salariu_maxim) {
      printf("Angajatul %s are salariul maxim (%lf)\n", ang.nume, ang.salariu);
    }
  }

  fclose(fin);
  free(ang.nume);
}

void stergere_angajat(char cnp[LEN_CNP]) {
  Angajat ang;
  ang.nume = (char *)malloc(LEN_NUME * sizeof(char));

  // varianta naiva: facem un fisier nou in care copiem toti angajatii mai
  // putin cel cu cnp-ul dat ca parametru
  FILE *fin = fopen("angajati.bin", "rb");
  FILE *fout = fopen("tmp.bin", "wb");

  while (1) {
    int succes = fread(ang.nume, sizeof(char), LEN_NUME, fin);
    if (succes == 0)
      break;

    fread(ang.cnp, sizeof(char), LEN_CNP, fin);
    fread(&ang.varsta, sizeof(int), 1, fin);
    fread(&ang.salariu, sizeof(double), 1, fin);

    // nu scriu angajatul cu cnp-ul cnp
    if (strcmp(cnp, ang.cnp) == 0)
      continue;

    fwrite(ang.nume, sizeof(char), LEN_NUME, fout);
    fwrite(ang.cnp, sizeof(char), LEN_CNP, fout);
    fwrite(&ang.varsta, sizeof(int), 1, fout);
    fwrite(&ang.salariu, sizeof(double), 1, fout);
    fflush(fout);
  }

  fclose(fin);
  fclose(fout);
  free(ang.nume);

  rename("tmp.bin", "angajati.bin");
}

int main() {
  scrie_angajati_bin();
  afisare_dupa_cnp("9999999999999"); // nu exista
  afisare_dupa_cnp("1234565432456"); // miPlacFisiereleBinare

  adaugare_angajat();                // il adaug pe Adaugel
  afisare_dupa_cnp("3678909256789"); // trebuie sa il gaseasca pe Adaugel

  scriere_angajati_txt();

  afisare_angajati_salariu_maxim();

  stergere_angajat("3678909256789"); // il sterg pe Adaugel
  afisare_dupa_cnp("3678909256789"); // adaugel nu mai exista
}