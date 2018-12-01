#include <stdio.h>
#include <stdlib.h>

// Functie care afiseaza adresa fiecarui element dintr-o
// matrice. Scopul e sa vedem ca o matrice declarata cu:
// tip nume_variabile[numar_linii][numar_coloane];
// va avea toate elementele intr-un bloc contiguu de memorie:
// adica le vom gasi in memorie astfel:
// mat[0][0] mat[0][1] ... mat[0][n - 1] mat[1][0] mat[1][1] etc
// (unde n e dimensiunea matricii)
void print_mat_elem_address(int n, int mat[][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%p ", &(mat[i][j]));
    }
    printf("\n");
  }
}

// E echivalent cu a scrie:
//
// print_matrix_v1(int n, int mat[n][n])
// sau
// print_matrix_v1(int n, int (*mat)[n])
//
// (La array-uri multidimensionale, doar prima
// dimensiune poate sa nu fie mentionata)
void print_matrix_v1(int n, int mat[][n]) {
  printf("Print matrix v1\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // In loc de mat[i][j] putem scrie oricare dintre
      // variantele:
      printf("%d ", (*(mat + i))[j]);
      // printf("%d ", *((*(mat + i)) + j));
      // printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

void print_matrix_v2(int n, int **mat) {
  printf("Print matrix v2\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // In loc de mat[i][j] putem scrie oricare dintre
      // variantele:
      printf("%d ", (*(mat + i))[j]);
      // printf("%d ", *((*(mat + i)) + j));
      // printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int n = 3;

  int mat1[100][100];
  int mat2[n][n]; // va avea dimensiune n x n
  int *mat3[100]; // va avea dimensiune 100 x 100
  int *mat4[n];   // va fi de dimendiune n x n
  int **mat5;     // tot dimensiune n x n dupa alocare

  // Alocare dinamica pentru variabilele care sunt pointer

  // mat3 este un vector de 100 pointeri. Trebuie sa aloc
  // fiecare pointer mat3[i] in parte.
  for (int i = 0; i < 100; i++) {
    mat3[i] = (int *)malloc(100 * sizeof(int));
  }

  // La fel ca mai sus, doar ca mat4 are n elemente, nu 100.
  for (int i = 0; i < n; i++) {
    mat4[i] = (int *)malloc(100 * sizeof(int));
  }

  // Aloc mai intai un vector de vectori, iar apoi fiecare
  // vector in parte.
  mat5 = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    mat5[i] = (int *)malloc(n * sizeof(int));
  }

  // Populez 3 x 3 elemente din fiecare matrice
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mat1[i][j] = i * 3 + j + 1;
      mat2[i][j] = i * 3 + j + 1;
      mat3[i][j] = i * 3 + j + 1;
      mat4[i][j] = i * 3 + j + 1;
      mat5[i][j] = i * 3 + j + 1;
    }
  }

  // O sa afiseze corect doar prima linie. De ce ?
  //
  // In C, in general, a[i] este expandat de compilator la
  // *(a + i)
  // (motiv pentru care putem sa scriem si dubiosenii
  // de genul 2[a] ca sa accesam elementul de pe pozitia 2
  // din a - don't use that!)
  //
  // La matrice, noi trebuie sa specificam intotdeauna numarul
  // de coloane pentru ca mat[i][j] va fi expandat ca
  // *(mat + i * dimensiune_coloana + j)
  // (asta pentru ca o matrice declarata cu
  //
  // int mat[..][..];
  //
  // si nu cu pointeri
  // va fi intotdeauna alocata intr-un bloc contiguu de memorie -
  // putem verifica asta apeland print_mat_elem_address(n, mat2);)
  //
  // Pasand n = 3 pentru matricea care a fost declarata cu dim 100x100,
  // elementele vor fi accesate astfel:
  // mat[0][0] <=> *(mat + 0 * 3 + 0) = *mat
  // mat[0][1] <=> *(mat + 0 * 3 + 1) = *(mat + 1)
  // mat[0][2] <=> *(mat + 0 * 3 + 2) = *(mat + 2)
  // (deci prima linie va fi accesata corect)
  // Apoi:
  // mat[1][0] <=> *(mat + 1 * 3 + 0) = *(mat + 3)
  // Cu toate astea, in main, noi avem matricea declarata cu dimensiune 100,
  // deci acolo mat[1][0] se expandeaza de fapt la *(mat + 1 * 100 + 0)
  //
  print_matrix_v1(3, mat1);

  // Nu compileaza: print_matrix_v1 asteapta ceva de tipul int**,
  // in timp ce matricea noastra este vazuta de compilator ca
  // int (*)[100]
  // print_matrix_v2(3, mat1);

  // Aici matricea are elemente populate fix cat dimensiunea ei
  // Se printeaza corect.
  print_matrix_v1(3, mat2);

  // Nu compileaza:
  // print_matrix_v2(3, mat2);

  // Nu compileaza:
  // print_matrix_v1(3, mat3);

  print_matrix_v2(3, mat3);

  // Nu compileaza:
  // print_matrix_v1(3, mat4);

  print_matrix_v2(3, mat4);

  // Nu compileaza:
  // print_matrix_v1(3, mat5);

  print_matrix_v2(3, mat5);

  // Concluzii:
  // 1. cat timp am declarat mat cu cel putin un *,
  // el va fi vazut ca avand tip 'int **', deci va compila
  // doar print_matrix_v2.

  // 2. Daca avem matricea declarata static, cand este
  // pasata ca argument unei functii, trebuie sa mentionam
  // acelasi numar de coloane ca atunci cand am declarat-o.
}