void print_binary(char c) {
  int bits[8];
  memset(bits, 0, sizeof(bits));

  for (unsigned i = 0; i <= 7; i++) {
    if (c & (1 << i)) {
      bits[i] = 1;
    }
  }

  for (int i = 7; i >= 0; i--) {
    printf("%d", bits[i]);
  }
  printf("\n");
}

typedef struct {
  // Standardul C nu specifica daca char este signed sau nu, asa ca vom
  // declara campurile ca unsigned pentru a ne asigura ca nu se pierde un bit
  // pentru semn.

  // Varsta < 65 => trebuie sa putem reprezenta de la 0 la 64 inclusiv
  // 64 in binar este 1000000, deci avem nevoie de maxim 7 biti
  unsigned char varsta : 7;

  // Norma este 0 pentru part-time si 1 pentru full-time.
  unsigned char norma : 1;

  // Nu avem ce optimiza aici.
  char nume[30];

  // Fiecare digit din cnp este >= 0 si <= 9, deci poate fi reprezentat
  // pe 4 biti (adica jumatate de char). Cum CNP-ul are 13 caractere, definim
  // un array de 7 char-uri, avand conventia ca ultimii 4 biti din cnp[i]
  // reprezinta cifra 2 * i din cnp, iar primii 4 biti din cnp[i] reprezinta
  // cifra 2 * i + 1 din cnp.
  unsigned char cnp[7];
} Angajat;

void pretty_print_angajat(Angajat a) {
  printf("Angajat %s cu varsta %d, ", a.nume, (int)a.varsta);
  if (a.norma)
    printf("full-time ");
  else
    printf("part-time ");

  for (int i = 0; i <= 6; i++) {
    // Daca vreti sa vedeti reprezentarea binara a CNP-ului, decomentati:
    // print_binary(a.cnp[i]);

    int digit0 = a.cnp[i] & (((char)1 << 4) - 1); // ultimii 4 biti din cnp[i]
    int digit1 =
        (a.cnp[i] >> 4) & (((char)1 << 4) - 1); // primii 4 biti din cnp[i]

    // Primii 6 chars tin cate 2 digiti fiecare
    if (i != 6)
      printf("%d%d", digit0, digit1);
    // Ultimul char tine doar ultimul digit din CNP
    else
      printf("%d\n", digit0);
  }
}

Angajat read_angajat() {
  Angajat a;
  memset(&a, 0, sizeof(a));

  // Din nou, trebuie sa folosim variabile auxiliare, deoarece nu putem citi
  // direct campurile de biti (nu avem acces la adresa lor).
  unsigned varsta;
  scanf("%u", &varsta);

  if (varsta >= 65) {
    printf("Varsta trebuie sa fie mai mica decat 65.\n");
    exit(-1);
  }

  // Daca nu facem cast, varsta nu are tipul char, ci unsigned, asa cum
  // l-am declarat.
  a.varsta = (char)varsta;

  int norma;
  scanf("%d", &norma);

  if (norma != 0 && norma != 1) {
    printf("Norma trebuie sa fie 1 pentru full-time si 0 pentru part-time.\n");
    exit(-1);
  }

  a.norma = (char)norma;

  // Numele il pot citi direct pentru ca nu e camp de biti.
  scanf("%s", a.nume);

  for (int i = 0; i < 13; i++) {
    char digit;
    scanf(" %c", &digit);

    if (digit < '0' || digit > '9') {
      printf("CNP-ul trebuie sa contina 13 cifre.\n");
      exit(-1);
    }

    // Daca i este impar, trebuie sa setam primii 4 biti din a.cnp[i / 2]
    if (i & 1) {
      a.cnp[i / 2] |= (char)(digit - '0') << 4;
    }
    // Daca i este par, setam ultimii 4 biti din a.cnp[i / 2]
    else {
      a.cnp[i / 2] |= (char)(digit - '0');
    }
  }

  return a;
}
