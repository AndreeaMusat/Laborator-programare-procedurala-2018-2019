#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 50
#define MAX_LINE_LEN 255

typedef struct NumarMare {
  // data[0] = numarul de cifre (trebuie sa fie maxim 255)
  // data[1] = unitati
  // data[2] = zeci
  // etc
  unsigned char *data;
} NumarMare;

void inverseaza(char *line) {
  int left = 0;
  int right = strlen(line) - 1;
  unsigned char aux;

  // Interschimb primul digit cu ultimul, al doilea cu penultimul, etc.
  while (left < right) {
    aux = line[left];
    line[left] = line[right];
    line[right] = aux;
    left++, right--;
  }
}

void citire_numar_mare(FILE *fin, NumarMare *num) {
  char line[MAX_LINE_LEN];
  memset(line, 0, sizeof(line));

  fgets(line, MAX_LINE_LEN, fin);

  // Sterg newline de la finalul liniei citite din fisier
  // (pun manual '\0' care marcheaza finalul unui sir)
  int line_len = strlen(line);
  if (line[line_len - 1] == '\n') {
    line[line_len - 1] = '\0';
    line_len -= 1;
  }

  num->data = (unsigned char *)calloc(1 + line_len, sizeof(unsigned char));

  // In struct trebuie sa tin digitii in ordinea asta: unitati, zeci, sute, ...
  // Le citim din fisier in ordine inversa, deci inversam linia
  inverseaza(line);

  // Copiez numarul incepand cu pozitia 1 din array
  strcpy(num->data + 1, line);

  // Pozitia 0 trebuie sa fie numarul de cifre
  num->data[0] = (char)line_len;
}

void afisare_numar_mare(FILE *fout, NumarMare num) {
  char data[MAX_LINE_LEN];
  strcpy(data, num.data + 1);
  inverseaza(data);

  fprintf(fout, "Numar: %s cu %d cifre\n", data, (int)num.data[0]);
}

void calcul_suma(NumarMare num1, NumarMare num2, NumarMare *result) {
  int len_max = num1.data[0] >= num2.data[0] ? num1.data[0] : num2.data[0];

  // Deocamdata consideram ca rezultatul are acelasi numar de cifre ca numarul
  // mai mare dintre cele 2. (e posibil sa avem carry la ultimul pas)
  result->data = (unsigned char *)calloc(1 + len_max, sizeof(unsigned char));
  result->data[0] = len_max;

  int carry = 0;

  for (int i = 1; i <= len_max; i++) {
    // Digitul curent reprezinta suma celor 2 digiti din fiecare numar (daca
    // exista!! - daca nu, adunam '0'
    // - asta se poate intampla doar cand numerele nu au aceeasi lungime) +
    // carry-ul de la pasul trecut
    int digit = carry + (i - 1 < num1.data[0] ? num1.data[i] : '0') +
                (i - 1 < num2.data[0] ? num2.data[i] : '0');

    // Avem grija sa scadem de 2 ori '0', deoarece num->data este in format char
    digit -= 2 * '0';

    // printf("digit is %d\n", digit);

    // Ne asiguram ca digit nu e mai mare ca 10 si setam corect carry-ul
    if (digit >= 10) {
      carry = 1;
      digit = digit % 10;
    } else {
      carry = 0;
    }

    result->data[i] = (char)(digit + '0');
  }

  // E posibil ca la final sa raman cu un carry (de ex daca adun 99 + 1,
  // rezultatul o sa aiba cu un digit mai
  // mult decat numarul maxim dintre 99 si 1)
  if (carry) {
    result->data[0] += 1;
    result->data = (unsigned char *)realloc(result->data, result->data[0] + 1);
    result->data[result->data[0]] = '1';
  }
}

void calcul_produs(NumarMare num1, NumarMare num2, NumarMare *result) {

  // Daca unul dintre numere e 0, returnez 0
  if ((num1.data[0] == 1 && num1.data[1] == '0') ||
      (num2.data[0] == 1 && num2.data[1] == '0')) {
    result->data = (unsigned char *)calloc(2, sizeof(unsigned char));
    result->data[0] = 1;
    result->data[1] = 0;
    return;
  }

  int result_len = (int)num1.data[0] + (int)num2.data[0];
  result->data = (unsigned char *)calloc(result_len + 1, sizeof(unsigned char));

  for (int i = 1; i <= result_len; i++) {
    result->data[i] = '0';
  }

  // Inmultesc num1 cu fiecare digit din num2 si la fiecare pas adaug la result
  // Cand adaug la result inmultirea cu digitul i din num2, trebuie sa shiftez
  // rezultatul curent cu i - 1 pozitii:
  // De exemplu:
  // 			1259 x
  // 		   27381
  //     ---------
  //          1259	-> La i = 0, pun 1259 in result
  // 		  10072		-> La i = 1, adun rezultatul inmultirii curente (10072),
  // dar incepand cu indexul 1
  // 		  3777
  //        etc
  for (int i = 1; i <= num2.data[0]; i++) {
    char tmp_result[2 + num1.data[0]];
    memset(tmp_result, 0, sizeof(tmp_result));

    // in tmp_result[] tin rezultatul inmultirii lui num2 cu digitul i - 1 din
    // num1
    int carry = 0;
    for (int j = 1; j <= num1.data[0]; j++) {
      int digit = (int)(num2.data[i] - '0') * (int)(num1.data[j] - '0') + carry;

      if (digit >= 10) {
        carry = digit / 10;
        digit = digit % 10;
      } else {
        carry = 0;
      }

      tmp_result[j - 1] = (char)(digit + '0');
    }

    if (carry) {
      tmp_result[num1.data[0]] = (char)(carry + '0');
    }

    // printf("TMP result = %s\n", tmp_result);

    // Adun tmp_res shiftat la rezultat
    carry = 0;
    for (int j = 0; j < strlen(tmp_result); j++) {
      int digit =
          (int)(tmp_result[j] - '0') + (int)(result->data[j + i] - '0') + carry;

      if (digit >= 10) {
        carry = digit / 10;
        digit = digit % 10;
      } else {
        carry = 0;
      }

      result->data[j + i] = (char)('0' + digit);
    }

    if (carry) {
      result->data[strlen(tmp_result) + i] = (char)('0' + carry);
    }

    // printf("RESULT NOW:\n");
    // afisare_numar_mare(stdout, *result);

    if (i == num2.data[0]) {
      result->data[0] = strlen(tmp_result) - 1 + i + (carry == 0 ? 0 : 1);
    }
  }
}

int main() {
  char filename[MAX_FILENAME_LEN];
  scanf("%s", filename);

  FILE *fin = fopen(filename, "rt");
  if (fin == NULL) {
    fprintf(stderr, "Nu am putut deschide fisierul %s pentru citire.\n",
            filename);
    exit(-1);
  }

  NumarMare num1, num2;
  citire_numar_mare(fin, &num1);
  citire_numar_mare(fin, &num2);
  fclose(fin);

  afisare_numar_mare(stdout, num1);
  afisare_numar_mare(stdout, num2);

  NumarMare suma, produs;
  calcul_suma(num1, num2, &suma);
  calcul_produs(num1, num2, &produs);

  // Deschid acelasi fisier pentru scrierea sumei si produsului la final - fol
  // mod 'append'
  FILE *fout = fopen(filename, "a");
  if (fout == NULL) {
    fprintf(stderr, "Nu am putut deschide fisierul %s in modul append\n",
            filename);
    exit(-1);
  }

  afisare_numar_mare(fout, suma);
  afisare_numar_mare(fout, produs);

  free(num1.data);
  free(num2.data);
  free(suma.data);
  free(produs.data);
}
