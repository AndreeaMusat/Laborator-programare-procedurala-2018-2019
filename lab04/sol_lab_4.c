#include <stdio.h>
#include <stdlib.h>

#include "extra.h"
#include "locuinta.h"
#include "angajati.h"

void test_ex_1() {
  // Try: e.num = 18246. What happens ? Why ?
  EndianUnion e;
  scanf("%hu", &e.num);
  printf("%c %c\n", e.bytes[0], e.bytes[1]);

  char tmp = e.bytes[0];
  e.bytes[0] = e.bytes[1];
  e.bytes[1] = tmp;

  printf("%c %c\n", e.bytes[0], e.bytes[1]);
  printf("%hu\n", e.num);
}

void test_ex_2() {
  int n;
  char line[1024];
  Locuinta loc[1024];

  printf("Introduceti numarul n de locuinte (n < 1024):\n");
  fgets(line, 10, stdin);
  sscanf(line, "%d", &n);

  // Setez toata memoria ocupata de variabila loc cu zerouri
  // ca sa nu avem probleme cu valori reziduale.
  // memset(pointer la adresa unde vrem sa setam, ce valoare vrem sa setam,
  // dimensiunea zonei de memorie).
  memset(loc, 0, sizeof(loc));
  memset(line, 0, sizeof(line));

  for (int i = 0; i < n; i++) {
  	loc[i] = read_locuinta();
  }

  // Parcurg toate locuintele si retin indexul locuintei de tip garsoniera
  // care are balcon si suprafata cea mai mare.
  int idx_garsoniera = index_garsoniera_max_balcon(loc, n);

  if (idx_garsoniera != -1) {
    printf("Garsoniera cu balcon si cea mai mare suprafata este:\n");
    pretty_print_locuinta(loc[idx_garsoniera]);
  } else {
  	printf("Nu am gasit nicio garsoniera care sa indeplineasca criteriile\n");
  }
}

void test_ex_3() {
  printf("Sizeof(Angajat) = %lu\n", sizeof(Angajat));

  Angajat a = read_angajat();
  pretty_print_angajat(a);
}

void test_ex_4() {
  // Memoria ocupata va fi de 2 octeti, deoarece toate campurile sunt pe 1 bit, 
  // deci incap toate intr-o singura variabila de tip unsigned short.
  // Se poate mai bine ?
  // Da, am putea incerca sa punem toate campurile intr-un char.
  printf("Sizeof(DocumentePrezenteShort) = %lu\n", sizeof(DocumentePrezenteShort));
  printf("Sizeof(DocumentePrezenteChar) = %lu\n", sizeof(DocumentePrezenteChar));

}

int main() {
  // test_ex_1();
  // test_ex_2();
  test_ex_3();
  // test_ex_4();
}