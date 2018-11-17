#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
  int id;
  char nume[20];
  char prenume[20];
  float nota;
} Student;

void exit_if_null_file(char *nume_fisier, FILE *f) {
  if (f == NULL) {
    fprintf(stderr, "Nu am putut deschide fisierul %s.\n", nume_fisier);
    exit(-1);
  }
}
// să se citească datele de la tastatură pentru n studenți
// și să se memoreze într-un fișier binar (transmis ca parametru)
void creare(char *nume_fisier_binar, int n) {
  // Deschid fisierul binar in modul scriere ("w" il creeaza
  // daca nu exista; daca exista, ii sterge continutul)
  FILE *out = fopen(nume_fisier_binar, "wb");
  exit_if_null_file(nume_fisier_binar, out);

  Student stud;
  for (int i = 0; i < n; i++) {
    // Citesc datele unui student de la tastatura
    scanf("%d %20s %20s %f", &stud.id, stud.nume, stud.prenume, &stud.nota);

    // Scriu datele studentului in fisier
    fwrite(&stud, sizeof(Student), 1, out);
  }

  // Inchid fisierul
  fclose(out);
}

// să se citească datele din fișierul binar si să se afișeze într-un alt fișier
// text
void afisare(char *nume_fisier_binar, char *nume_fisier_text) {
  FILE *in = fopen(nume_fisier_binar, "rb");
  FILE *out = fopen(nume_fisier_text, "w");

  exit_if_null_file(nume_fisier_binar, in);
  exit_if_null_file(nume_fisier_text, out);

  Student stud;
  // Pentru ca fread intoarce numarul de elemente citite cu succes din fisier,
  // il pot folosi pe post de conditie pentru un loop while: (Altfel nu stiu
  // cati studenti trebuie sa citesc din fisier)
  while (fread(&stud, sizeof(Student), 1, in)) {
    fprintf(out, "Student %s %s cu id %d si nota %.2f\n", stud.nume,
            stud.prenume, stud.id, stud.nota);
  }

  fclose(in);
  fclose(out);
}

void modificare(char *nume_fisier_binar, int id, float nota) {
  FILE *f = fopen(nume_fisier_binar, "r+b");
  exit_if_null_file(nume_fisier_binar, f);

  // Citesc rand pe rand studentii din fisier si determin al catelea
  // este cel cu id-ul id.
  Student stud;
  int cnt = 0;
  int found = -1; // idx la care am gasit studentul
  while (1) {
    size_t succ = fread(&stud, sizeof(stud), 1, f);
    if (succ == 0)
      break;

    if (stud.id == id) {
      found = cnt;
      break;
    }

    ++cnt;
  }

  // Daca nu am gasit studentul, afisez un mesaj
  if (found == -1) {
    fprintf(stderr, "Nu a fost gasit studentul cu id-ul %d.\n", id);
    fclose(f);
    return;
  }

  // Studentul cu id-ul cautat este chiar ultimul citit din fisier
  // (am dat break imediat dupa), deci pentru a muta cursorul in
  // dreptul notei acestuia, trebuie sa mergem inapoi cu sizeof(float)
  // fata de pozitia curenta a cursorului in fisier.
  fseek(f, -sizeof(float), SEEK_CUR);
  fwrite(&nota, sizeof(float), 1, f);
  fclose(f);
}

// să se adauge date pentru un nou student în fișierul binar:
void adaugare(char *nume_fisier_binar, Student stud) {
  // Deschid fisierul in modul "append" pentru a adauga un nou
  // student la finalul acestuia
  FILE *f = fopen(nume_fisier_binar, "a");
  exit_if_null_file(nume_fisier_binar, f);

  fwrite(&stud, sizeof(Student), 1, f);
  fclose(f);
}

void test() {
  int num_students;
  scanf("%d", &num_students);

  // Cream fisierul "all_students.bin" cu datele a num_student studenti.
  creare("all_students.bin", num_students);
  afisare("all_students.bin", "all_students.txt");

  // Citim de la tastatura datele pentru un nou student pe care il vom
  // adauga in all_students.bin si scriem intregul continut in
  // all_students_adaugat.txt
  Student new_stud;
  scanf("%d %s %s %f", &new_stud.id, new_stud.nume, new_stud.prenume,
        &new_stud.nota);
  adaugare("all_students.bin", new_stud);
  afisare("all_students.bin", "all_students_adaugat.txt");

  // Modific nota studentului cu id 5 si scriu tot continutul in
  // all_students_modificat.txt
  modificare("all_students.bin", 5, 10.0);
  afisare("all_students.bin", "all_students_modificat.txt");

  // Modific nota studentului cu id 9999 (inexistent - se afiseaza mesaj de
  // eroare)
  modificare("all_students.bin", 9999, 10.0);
}

int main() {
  test();
  return 0;
}