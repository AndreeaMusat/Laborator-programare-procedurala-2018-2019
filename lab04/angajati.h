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
  if (a.norma) printf("full-time ");
  else printf("part-time ");

  // TODO: print CNP
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

  // TODO: citire cnp

  return a;
}