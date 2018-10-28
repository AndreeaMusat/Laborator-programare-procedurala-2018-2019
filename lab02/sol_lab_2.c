#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Parcurgem numarul de la stanga catre dreapta,
// avand grija sa nu afisam 0-urile pana nu gasim primul bit de 1.
void print_binary(int n) {
  // Vrem ca i sa fie de forma 10000...000 la inceput
  // (unde numarul de 0-uri trebuie sa fie egal cu numar
  // total biti - 1), pentru a putea verifica valoarea
  // primului bit al numarului.
  // Ulterior, vrem ca i sa fie, pe rand
  // 010000....0,
  // 001000....0,
  // 000100....0
  // ........
  // 00000000001
  // si folosim i pentru a verifica valoarea fiecarui bit
  int found_first_one = 0;
  for (int i = (sizeof(int) * 8 - 1); i >= 0; i--) {
    if ((n & (1 << i)) != 0) {
      // Daca nu am mai gasit un bit 1, marchez gasirea lui.
      if (found_first_one == 0) {
        found_first_one = 1;
      }
      printf("1");
    }
    // Afisez zero-urile doar daca ele apar dupa primul bit de 1.
    else if (found_first_one) {
      printf("0");
    }
  }

  printf("\n");
}

void test_ex_1() {
  int test_values[] = {10, 1024, -34, 89999};

  printf("Test exercitiu 1...\n");
  for (int i = 0; i < sizeof(test_values) / sizeof(int); i++) {
    printf("Reprezentarea in binar a lui %d este ", test_values[i]);
    print_binary(test_values[i]);
  }
}

void test_ex_2() {
  short number, bit;

  printf("Introduceti un numar intre %hd si %hd si un bit intre 0 si 15\n",
         SHRT_MIN, SHRT_MAX);

  // Atentie! Un short il citim cu "%hd", altfel scanf o sa incerce
  // sa acceseze memorie in mod ilegal.
  scanf(" %hd %hd", &number, &bit);

  if (bit < 0 or bit > 15) {
    printf("Bit trebuie sa fie intre 0 si 15!\n");

    // exit(-1) e echivalent cu return -1; in main
    // Conventional, cand main() intoarce o valoare != 0, semnalam
    // o eroare.
    exit(-1);
  }

  printf("Numarul %hd in binar este: ", number);
  print_binary(number);

  // Setam bit facand SAU cu o masca ce contine 1 pe pozitia care ne
  // intereseaza.
  printf("Numarul %hd in care setam bitul %hd este: %hd, adica: ", number, bit,
         number | (1 << bit));
  print_binary(number | (1 << bit));

  // Curatam un bit facand SI cu o masca ce contine 0 *doar* pe pozitia care
  // ne intereseaza.
  printf("Numarul %hd in care curatam bitul %hd este: %hd, adica: ", number,
         bit, number & (~(1 << bit)));
  print_binary(number & (~(1 << bit)));

  // Complementam un bit facand XOR cu o masca ce contine 1 pe pozitia bit.
  printf("Numarul %hd in care complementam bitul %hd este: %hd, adica: ",
         number, bit, number ^ (1 << bit));
  print_binary(number ^ (1 << bit));
}

void test_ex_3() {
  printf("Se citesc întregii x, y, n, p. Să se copieze "
         "în x, începând din poziția p, ultimii n biți "
         "din y și să se afișeze noua valoare a lui x.\n");
  int x, y, n, p;
  scanf(" %d %d %d %d", &x, &y, &n, &p);

  printf("x in binar este: ");
  print_binary(x);
  printf("y in binar este: ");
  print_binary(y);

  // Presupunem ca ultimii n biti din y vor avea loc in x incepand
  // cu pozitia p.
  //
  // Pasul 1. Selectam ultimii n biti din y. Pentru asta avem nevoie
  // de o masca cu 1 pe ultimii n biti.
  // Stim ca 2^x - 1 este mereu un numar de forma 11111...1 (unde numarul
  // de 1-uri este chiar x) (Q: De ce ? A: Pentru ca 2^x este 10000...0, iar
  // 1000...0 - 1 = 11111....1 )
  int last_n_bits_in_y = y & ((1 << n) - 1);
  printf("Ultimii n biti din y sunt (0 din fata nu se vor afisa): ");
  print_binary(last_n_bits_in_y);

  // Pasul 2. Pentru ca vrem sa punem bitii selectati mai sus in x
  // incepand cu pozitia p, vrem sa 'curatam' n biti din x incepand cu
  // pozitia p, deci avem nevoie de o masca de forma: 11111100000...0001111
  // (unde avem 0 de la pozitia p la pozitia p - n + 1)
  //
  // Idea este sa facem mai intai o masca de forma: 11111 (cu n de 1)
  // Am vazut la pasul anterior ca putem face asta cu (1 << n) - 1.
  //
  // Dupa, vrem sa shiftam masca asta (astfel incat dupa ea sa avem p - n + 1
  // zerouri), adica ((1 << n) - 1) << (p - n + 1);
  //
  // La final, observam ca acum avem o masca de forma 111..111000...00
  // (in mod implicit, inaintea grupului de 1 avem tot zerouri), deci
  // trebuie doar sa negam aceasta masca pentru a obtine ce ne intereseaza.
  int mask = ~(((1 << n) - 1) << (p - n + 1));
  x &= mask;

  printf("Masca pentru curatarea bitilor este: ");
  print_binary(mask);
  printf("x & mask = ");
  print_binary(x);

  // Pasul 3. Setam n biti din x incepand cu p la valoarea last_n_bits_in_y.
  // In primul rand, vrem sa mutam acesti biti la stanga ca primul bit de 1
  // din last_n_bits_in_y sa fie pe pozitia p (salvam rezultatul in mask)
  //
  // Apoi, fac OR intre x si aceasta masca pentru a seta bitii.
  mask = last_n_bits_in_y << (p - n + 1);
  x |= mask;

  printf("Bitii aliniati sunt: ");
  print_binary(mask);
  printf("x dupa copierea ultimilor n biti din y incepand cu pozitia p: ");
  print_binary(x);
}

// n este un numar binar (dar reprezentat in zecimal) de forma:
// 0000
// 0001
// 0010
// 0011
// .etc
// 1111
// iar rezultatul este un char care reprezinta
// digitul corespunzator lui n in hex.
char get_hex_digit(int n) {
  int digit = 0;
  int pow = 0;

  while (n) {
    digit += (n % 10) * (1 << pow);
    n /= 10;
    pow += 1;
  }

  if (digit >= 0 and digit <= 9)
    return char('0' + digit);
  else
    return char('A' + digit - 10);
}

void test_ex_4() {
  // Obs: Pentru ca am stocat binary_no ca unsigned
  // si nu ca char* (ca sa nu folosesc operatii pe siruri
  // de caractere inainte de laborator), o sa mearga doar
  // pentru numere binare care nu au mai multe cifre
  // decat numarul maxim reprezentabil pe unsigned.

  // binary_no este unsigned, deci este in baza 10.
  unsigned binary_no;
  // Folsim un array de chars ca sa retinem digitii in hex.
  char hex_no[100];
  // Indexul care arata pozitia curenta in hex_no[].
  int cnt = 0;

  printf("Introduceti un numar binar\n");
  scanf(" %u", &binary_no);

  // Cat timp numarul e nenul, ne uitam la grupuri de cate 4
  // biti (de ce ?), le transformam intr-un digit in hex si
  // apoi le adaugam in array-ul hex_no, pe care la final il
  // parcurgem in ordine inversa pentru afisare.
  while (binary_no) {
    int rem = binary_no % 10000;
    hex_no[cnt++] = get_hex_digit(rem);
    binary_no /= 10000;
  }

  printf("Numarul corespunzator in hex este:\n");
  for (int i = cnt - 1; i >= 0; i--) {
    printf("%c", hex_no[i]);
  }
}

int sum_digits(int n) {
  int sum = 0;
  int rem = 0;

  while (n) {
    rem = n % 10;
    sum += rem;
    n /= 10;
  }

  return sum;
}

void test_ex_5() {
  int current = -1, previous = -1;

  printf("Introduceti numere intregi (0 pentru terminare) \n");
  while (1) {
    if (current != -1)
      previous = current;

    scanf(" %d", &current);
    if (current == 0)
      break;

    if (previous == -1)
      continue;

    if (previous % sum_digits(previous) == current) {
      printf("Am gasit o pereche! %d %d\n", previous, current);
    }
  }
}

void test_ex_6() {
  int p;

  printf("Introduceti un intreg p (perimetrul triunghiului)\n");
  scanf(" %d", &p);

  // E suficient sa cautam laturi pana la p / 2 (inclusiv!)
  // (altfel nu ar fi valabila inegalitatea a + b > c)
  for (int i = 1; i <= p / 2; i++) {
    for (int j = 1; j <= p / 2; j++) {
      int k = p - i - j;
      if (k <= 0)
        continue;

      // Verific inegalitatea pt toate perechile de laturi
      // si in plus i <= j <= k (ca sa fim siguri ca fiecare
      // triunghi posibil este afisat o singura data)
      if (i + j > k && i + k > j && j + k > i && i <= j && j <= k) {
        printf("Am gasit un triunghi! %d %d %d\n", i, j, k);
      }
    }
  }
}

int main() {
  // Exercitiul 1. Afisare numar in binar.
  // test_ex_1();

  // Exercitiul 2. Setare, curatare si complementare bit.
  // test_ex_2();

  // Exercitiul 3. *complicated...*
  test_ex_3();

  // Exercitiul 4. bin2hex (fara baza 10 intermediar)
  // test_ex_4();

  // Exercitiul 5.
  // test_ex_5();

  // Exercitiul 6.
  // test_ex_6();
}
