#include <stdio.h>
#include <string.h>

#define MAX_LEN 1023

typedef struct {
  short sign;
  short digits[MAX_LEN];
  size_t num_digits;
} LongInteger;

LongInteger read_long_integer() {
  char line[MAX_LEN + 1];

  // Fiecare numar se afla pe o linie.
  fgets(line, sizeof(line), stdin);

  size_t len = strlen(line);

  // fgets() citeste inclusiv endl ('\n'), deci
  // trebuie sa il eliminam.
  if (line[len - 1] == '\n')
    line[len - 1] = '\0';

  LongInteger li;

  // Setam toata zona de memorie ocupata de li cu 0.
  // Initial numarul nu are nicio cifra.
  // Setam toti digitii cu 0 (va fi util mai tarziu cand
  // adunam numere care au lungimi diferite)
  memset(&li, 0, sizeof(li));

  // for (int i = 0; i < MAX_LEN; i++)
  // 	printf("%hd\n", li.digits[i]);

  // Semnul numarului e minus daca linia incepea cu '-'.
  li.sign = (line[0] == '-' ? -1 : 1);

  // Daca semnul e minus, ciferele incep de la indexul 1
  // din line, altfel incep de la 0.
  for (int i = (li.sign == 1 ? 0 : 1); i < len; i++) {
    if ((line[i] >= '0') && (line[i] <= '9')) {
      li.digits[li.num_digits++] = line[i] - '0';
    }
  }

  return li;
}

void print_long_integer(LongInteger li) {
  if (li.num_digits == 0) {
    printf("0");
    return;
  }

  // Afisam numerele negative intre paranteze.
  if (li.sign == -1)
    printf("(-");

  for (int i = 0; i < li.num_digits; i++) {
    printf("%d", li.digits[i]);
  }

  if (li.sign == -1)
  	printf(")");
}

// li trebuie pasat ca pointer. Daca il pasam ca LongInteger li,
// in momentul apelarii functiei reverse_long_integer() se va face
// o copie a parametrului, iar functia o va modifica local pe aceasta,
// deci schimbarile nu vor fi vizibile in locul unde am apelat functia.
void reverse_long_integer(LongInteger *li) {
  int left = 0;
  int right = li->num_digits - 1;
  short aux;

  // Interschimb primul digit cu ultimul, al doilea cu penultimul, etc.
  while (left < right) {
    aux = li->digits[left];
    li->digits[left] = li->digits[right];
    li->digits[right] = aux;
    left++, right--;
  }
}

LongInteger add_unsigned_long_integers(LongInteger li1, LongInteger li2) {
  LongInteger result;
  memset(&result, 0, sizeof(result));

  size_t i, max_len = (li1.num_digits > li2.num_digits ? li1.num_digits
                                                       : li2.num_digits);

  int carry = 0, digit;
  for (i = 0; i < max_len; i++) {
    digit = li1.digits[i] + li2.digits[i] + carry;
    carry = digit / 10;
    digit = digit % 10;
    result.digits[result.num_digits++] = digit;
  }

  if (carry)
    result.digits[result.num_digits++] = 1;

  // Am facut calculul in ordine inversa, deci trebuie sa inversez rezultatul.
  reverse_long_integer(&result);

  return result;
}

// Compara modulele celor doua numere.
// Returnez:
// 		1 daca li1 > li2
// 		0 daca sunt egale
// 	   -1 daca li1 < li2
int compare_abs_long_integers(LongInteger li1, LongInteger li2) {
  if (li1.num_digits != li2.num_digits) {
    return li1.num_digits > li2.num_digits ? 1 : -1;
  }

  // Daca au acelasi numar de cifre, le compar.
  for (int i = 0; i < li1.num_digits; i++) {
    if (li1.digits[i] != li2.digits[i]) {
      return li1.digits[i] > li2.digits[i] ? 1 : -1;
    }
  }

  return 0;
}

// Trebuie ca li sa fie inversul unui numar atunci cand este apelata
// aceasta functie.
void remove_leading_zeros_long_integer(LongInteger *li) {
  for (int i = li->num_digits - 1; i >= 0; i--) {
    if (li->digits[i] == 0) {
      li->num_digits--;
    } else break;
  }
}

LongInteger subtract_long_integers(LongInteger li1, LongInteger li2) {
  LongInteger result;
  memset(&result, 0, sizeof(result));

  size_t i, max_len = (li1.num_digits > li2.num_digits ? li1.num_digits
                                                       : li2.num_digits);

  int borrowed = 0, digit;
  for (i = 0; i < max_len; i++) {
    digit = li1.digits[i] - li2.digits[i] - (borrowed ? 1 : 0);
    borrowed = (digit < 0);
    if (borrowed)
      digit += 10;
    result.digits[result.num_digits++] = digit;
  }

  // La scadere, e posibil ca rezultatul sa contina 'leading zeros' (zero in
  // fata
  // digitilor semnificativi din numar);
  // De exemplu 980 + (-980) = 000
  // Trebuie sa eliminam zerourile acestea
  remove_leading_zeros_long_integer(&result);

  // Am facut calculul in ordine inversa, deci trebuie sa inversez rezultatul.
  reverse_long_integer(&result);

  return result;
}

// li1 si li2 pot reprezenta numere pozitive sau negative.
LongInteger add_signed_long_integers(LongInteger li1, LongInteger li2) {
  LongInteger result;

  print_long_integer(li1);
  printf(" + ");
  print_long_integer(li2);

  // Daca au acelasi semn, le adunam.
  if (li1.sign == li2.sign) {
    reverse_long_integer(&li1);
    reverse_long_integer(&li2);

    // Aici populam doar result.digits si result.num_digits.
    result = add_unsigned_long_integers(li1, li2);

    // Semnul e acelasi cu al numerelor.
    result.sign = li1.sign;
  }
  // Altfel din cel mai mare il scadem pe cel mai mic, iar semnul e 1
  // daca li1 era mai mare, altfel -1
  else {
    int sign = compare_abs_long_integers(li1, li2);

    reverse_long_integer(&li1);
    reverse_long_integer(&li2);

    if (sign == 1) {
      result = subtract_long_integers(li1, li2);
    } else {
      result = subtract_long_integers(li2, li1);
    }

    result.sign = (sign == 1 ? li1.sign : li2.sign);
  }

  printf(" = ");
  print_long_integer(result);
  printf("\n\n");

  return result;
}

int main() {
  // Idee algoritm:
  // 1. Citesc numerele
  // 2. Le inversez ordinea cifrelor
  // 3. Le adun / scad si am grija sa pun semnul corespunzator la rezultat
  // 4. Setez semnul corespunzator rezultatului
  // 5. Inversez digitii rezultatului

  // Inputul va fi dat in formatul urmator:
  //
  // numar teste
  // numar_1_test_1
  // numar_2_test_1
  // etc
  //
  int num_tests, cnt = 0;
  char line[MAX_LEN];
  fgets(line, sizeof(line), stdin);
  sscanf(line, "%d", &num_tests);
  LongInteger result;

  while (cnt++ < num_tests) {
  	printf("Testul %d\n", cnt);
    LongInteger num1 = read_long_integer();
    LongInteger num2 = read_long_integer();
    result = add_signed_long_integers(num1, num2);
  }
}
