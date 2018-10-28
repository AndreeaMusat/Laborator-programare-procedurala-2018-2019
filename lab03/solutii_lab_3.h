#ifndef SOLUTII_LAB_3_H_
#define SOLUTII_LAB_3_H_

#define MAX_LEN_NUME 100
#define MAX_ELEMS 100
#define MIN_TRECERE 5
#define CALC_MEDIA(student)                                                    \
  0.4 * (student.nota_mate + student.nota_info) + 0.2 * student.nota_bac

typedef struct {
  int nr_legitimatie;
  char nume[MAX_LEN_NUME];
  float nota_mate;
  float nota_info;
  float nota_bac;
  float medie;
  int admis; // bool
  int buget; // bool
} Student;

typedef struct {
  // elems[i][0] = row of element i
  // elems[i][1] = column of element i
  // elems[i][2] = value of element i
  int elems[MAX_ELEMS][3];

  // Numarul curent de elemente nenule din matrice.
  int count_elems;
} SparseMatrix;

// TODO: struct polinom

#endif // SOLUTII_LAB_3_H_