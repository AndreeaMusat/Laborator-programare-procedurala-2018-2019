#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solutii_lab_3.h"

#define MAX_STUDENTS 1024

void test_ex_1() {
  char c = getchar();

  if (c >= 'A' && c <= 'Z') {
    c = (char)'a' + c - 'A';
  }

  putchar(c);
  putchar('\n');
}

void test_ex_2() {
  int a, b, result;
  char op;

  scanf("%d %c %d", &a, &op, &b);

  switch (op) {
  case '+': {
    result = a + b;
    break;
  }
  case '-': {
    result = a - b;
    break;
  }
  case '*': {
    result = a * b;
    break;
  }
  case '/': {
    if (b != 0) {
      result = a / b;
    } else {
      printf("Nu putem imparti la 0, sorry :(\n");
      exit(-1);
    }
    break;
  }
  case '%': {
    result = a % b;
  }
  default: {
    printf("Nu cunosc operatia %c, sorry :(\n", op);
    exit(-1);
  }
  }

  printf("result = %d\n", result);
}

int compare_names(const void *stud1, const void *stud2) {
  Student *s1 = (Student *)stud1;
  Student *s2 = (Student *)stud2;

  return strcmp(s1->nume, s2->nume);
}

int compare_grades(const void *stud1, const void *stud2) {
  Student *s1 = (Student *)stud1;
  Student *s2 = (Student *)stud2;

  return s1->medie < s2->medie;
}

void read_candidate(Student *all_candidates, int *cnt_students) {
  Student s;

  scanf(" %d %100s %f %f %f", &s.nr_legitimatie, &s.nume[0], &s.nota_mate,
        &s.nota_info, &s.nota_bac);

  // Folosim macro-ul definit in header.
  s.medie = CALC_MEDIA(s);
  s.admis = (s.medie > MIN_TRECERE) ? 1 : 0;

  all_candidates[*cnt_students] = s;
  *cnt_students += 1;
  qsort(all_candidates, *cnt_students, sizeof(Student), compare_names);
}

void print_candidates(Student all_candidates[], int cnt_students) {
  for (int i = 0; i < cnt_students; i++) {
    printf("Legitimatie: %d, Nume: %s, Nota mate: %.2f, Nota info %.2f,"
           " Nota bac: %.2f, MEDIE: %.2f, buget?: %d\n",
           all_candidates[i].nr_legitimatie, all_candidates[i].nume,
           all_candidates[i].nota_mate, all_candidates[i].nota_info,
           all_candidates[i].nota_bac, all_candidates[i].medie,
           all_candidates[i].buget);
  }
}

void fill_buget(Student all_candidates[], int cnt_students) {
  qsort(all_candidates, cnt_students, sizeof(Student), compare_grades);
  printf("CANDIDATII IN ORDINEA MEDIILOR:\n");
  print_candidates(all_candidates, cnt_students);

  // Cati studenti vor fi la buget ? 75%
  int count_buget = 0.75 * cnt_students;

  for (int i = 0; i < cnt_students; i++) {
    if (i < count_buget) {
      all_candidates[i].buget = 1;
    } else {
      all_candidates[i].buget = 0;
    }
  }
}

void test_ex_3() {
  Student all_candidates[MAX_STUDENTS];
  int cnt_students = 0;
  for (int i = 0; i < 5; i++)
    read_candidate(all_candidates, &cnt_students);

  printf("Studentii sortati in ordine alfabetica\n");
  print_candidates(all_candidates, cnt_students);

  fill_buget(all_candidates, cnt_students);
  printf("Studentii sortati in ordinea mediei (+ buget completat)\n");
  print_candidates(all_candidates, cnt_students);
}

SparseMatrix read_sparse_matrix() {
  SparseMatrix result;

  scanf("%d ", &result.count_elems);
  for (int i = 0; i < result.count_elems; i++) {
    // Citesc triplete de forma: linie, coloana, valoare.
    scanf("%d %d %d", &result.elems[i][0], &result.elems[i][1],
          &result.elems[i][2]);
  }

  return result;
}

void print_sparse_matrix(SparseMatrix m) {
  printf("Nr elem nenule: %d\n", m.count_elems);
  for (int i = 0; i < m.count_elems; i++) {
    printf("Row: %d, Col: %d, Val: %d\n", m.elems[i][0], m.elems[i][1],
           m.elems[i][2]);
  }
}

SparseMatrix add_sparse_matrices(SparseMatrix m1, SparseMatrix m2) {
  printf("M1 este:\n");
  print_sparse_matrix(m1);
  printf("M2 este:\n");
  print_sparse_matrix(m2);

  // Populez rezultatul cu elementele primei matrice.
  SparseMatrix result;
  result.count_elems = m1.count_elems;
  for (int i = 0; i < result.count_elems; i++) {
    result.elems[i][0] = m1.elems[i][0];
    result.elems[i][1] = m1.elems[i][1];
    result.elems[i][2] = m1.elems[i][2];
  }

  printf("Dupa copierea lui m1 in result, result este:\n");
  print_sparse_matrix(result);

  // Apoi iterez prin a doua matrice si caut liniar in rezultat
  // sa vad daca exista deja o valoare la pozitia respectiva.
  // Daca exista, adun la ea. Daca nu, creez o valoare noua.
  for (int i = 0; i < m2.count_elems; i++) {
    // Variabila semafor: Devine 1 atunci cand gasesc un element
    // din matricea rezultat care este pe aceeasi pozitie ca
    // elementul curent din m2.
    int found_elem = 0;
    for (int j = 0; j < result.count_elems; j++) {
      if ((m2.elems[i][0] == result.elems[j][0]) &&
          (m2.elems[i][1] == result.elems[j][1])) {
        result.elems[j][2] += m2.elems[i][2];

        found_elem = 1;
        // Pot sa ies din al doilea for loop, pentru ca stiu
        // sigur ca nu voi mai gasi alt element cu aceeasi linie
        // si coloana.
        break;
      }
    }

    // Daca nu am gasit niciun entry pe aceeasi pozitie, creez unul nou.
    if (!found_elem) {
      result.elems[result.count_elems][0] = m2.elems[i][0];
      result.elems[result.count_elems][1] = m2.elems[i][1];
      result.elems[result.count_elems][2] = m2.elems[i][2];

      // Incrementez numarul de elemente din matricea-rezultat.
      result.count_elems += 1;
    }
  }

  // Obs: matricea result poate sa nu aiba elementele sortate in
  // ordinea crescatoare a liniei (si apoi a coloanei)

  return result;
}

SparseMatrix multiply_sparse_matrices(SparseMatrix m1, SparseMatrix m2) {
  // Always initialize values!!!!!!
  SparseMatrix result2;
  result2.count_elems = 0;

  print_sparse_matrix(result2);

  for (int idx1 = 0; idx1 < m1.count_elems; idx1++) {
    for (int idx2 = 0; idx2 < m2.count_elems; idx2++) {
      // Daca linia pe care se afla al doilea element este diferita
      // de coloana pe care se afla primul element, atunci ele nu vor
      // fi inmultite.
      if (m1.elems[idx1][1] != m2.elems[idx2][0]) {
        continue;
      }

      // Cautam un element pe linia lui m1.elems[idx1] si coloana lui
      // m2.elems[idx2] in result2. Daca nu exista, cream unul.
      int found = 0;
      for (int idx_res = 0; idx_res < result2.count_elems; idx_res++) {
        if ((result2.elems[idx_res][0] == m1.elems[idx1][0]) &&
            (result2.elems[idx_res][1] == m2.elems[idx2][1])) {
          // Adaug produsul elementelor in result2at.
          result2.elems[idx_res][2] += m1.elems[idx1][2] * m2.elems[idx2][2];
          found = 1;
          break;
        }
      }

      if (!found) {
        printf("Creat element nou pe rand %d, coloana %d cu valoarea %d\n",
               m1.elems[idx1][0], m2.elems[idx2][1],
               m1.elems[idx1][2] * m2.elems[idx2][2]);

        result2.elems[result2.count_elems][0] = m1.elems[idx1][0];
        result2.elems[result2.count_elems][1] = m2.elems[idx2][1];
        result2.elems[result2.count_elems][2] =
            m1.elems[idx1][2] * m2.elems[idx2][2];

        result2.count_elems += 1;
      }
    }
  }

  // Obs: result2 poate sa nu aiba elementele sortate dupa linie.

  return result2;
}

void test_ex_4() {
  SparseMatrix m1 = read_sparse_matrix();
  SparseMatrix m2 = read_sparse_matrix();
  SparseMatrix added = add_sparse_matrices(m1, m2);
  printf("Rezultatul adunarii matricelor este:\n");
  print_sparse_matrix(added);

  SparseMatrix multiplied = multiply_sparse_matrices(m1, m2);
  printf("Rezultatul inmultirii matricelor este:\n");
  print_sparse_matrix(multiplied);
}

Polynomial read_polynomial() {
  Polynomial p;

  printf("Introduceti gradul, apoi coeficientii polinomului "
    "(incepand cu 0)\n");

  scanf(" %d", &p.degree);

  for (int i = 0; i <= p.degree; i++) {
    scanf(" %d", &p.coefs[i]);
  }

  return p;
}

void print_polynomial(Polynomial p) {
  for (int i = p.degree; i >= 0; i--) {
    printf("%d * x^%d", p.coefs[i], i);
    if (i != 0) printf(" + ");
  }

  printf("\n");
} 

Polynomial multiply_polynomials(Polynomial p1, Polynomial p2) {
  Polynomial result;
  result.degree = p1.degree + p2.degree;

  // Initializam coeficientii rezultatului cu 0.
  for (int i = 0; i <= result.degree; i++) {
    result.coefs[i] = 0;
  }

  for (int i = 0; i <= p1.degree; i++) {
    for (int j = 0; j <= p2.degree; j++) {
      result.coefs[i + j] += p1.coefs[i] * p2.coefs[j];
    }
  }

  return result;
}

void test_ex_5() {
  Polynomial p1 = read_polynomial();
  Polynomial p2 = read_polynomial();

  Polynomial result = multiply_polynomials(p1, p2);
  printf("Rezultatul inmultirii lui:\n");
  print_polynomial(p1);
  printf(" cu ");
  print_polynomial(p2);
  printf(" este ");
  print_polynomial(result);
}

int main() {
  // test_ex_1();
  // test_ex_2();
  // test_ex_3();
  // test_ex_4();
  test_ex_5();
}
