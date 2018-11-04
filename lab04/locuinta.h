#pragma once

#include <stdio.h>
#include <string.h>

typedef union {
  // Daca Locuinta e garsoniera, ne intereseaza daca are sau nu balcon.
  unsigned short balcon : 1;
  // Daca e apartament, poate fi Decomandat (D) sau Nedecomandat (N).
  char decomandat : 1;
  // Pentru casa retinem: 'pe sol' / 'parter+mansarda' / 'nr etaje'
  char casa_info[30];
} ExtraInfo;

typedef struct {
  char adresa[100];
  float suprafata;
  char tip_locuinta[30];
  int numar_camere;
  ExtraInfo info;
} Locuinta;

/* 
	
Deoarece adresa este formata din mai multe cuvinte, vom presupune
ca inputul va fi dat in formatul urmator:
n // numarul de locuinte ce va fi citit
adresa_casa_0
suprafata_casa_0, tip_locuinta_casa_0, numar_camere_casa_0
extra_info_casa_0
adresa_casa_1
suprafata_casa_1, tip_locuinta_casa_1, numar_camere_casa_1
extra_info_casa_1
etc

si vom citi fisierul linie cu linie, iar apoi vom extrage informatiile
din fiecare linie folosind functia sscanf, care este asemanatoare cu
scanf, doar ca face citirea dintr-un array de chars in loc sa o faca de
la tastatura.

scanf("%f %s %d", &f, &s, &n);

este echivalent cu:

char line[100];
memset(line, 0, sizeof(line)); // pun zerouri in toata zona de memorie ocupata de line
fgets(line, 100, stdin);
sscanf(line, "%f %s %d", &f, &s, &n);

Daca am fi folosit scanf() pentru adresa, citirea s-ar fi oprit dupa primul
cuvant din adresa.
*/
Locuinta read_locuinta() {
  Locuinta l;
  char line[1024];
  memset(&l, 0, sizeof(l));
  memset(line, 0, sizeof(line));

  // Prima linie: adresa
  fgets(l.adresa, 100, stdin);

  // A doua linie: suprafata, tip si numar camere
  memset(line, 0, sizeof(line));
  fgets(line, 1024, stdin);
  sscanf(line, "%f %30s %d", &l.suprafata, l.tip_locuinta, &l.numar_camere);

  // A treia linie: extra info (in functie de tip locuinta)
  memset(line, 0, sizeof(line));
  fgets(line, 1024, stdin);

  // In functie de tipul locuintei, in l.info tin alta informatie.
  // Obs: balcon, decomandat si casa_info sunt campuri de biti din union,
  // deci nu putem sa folosim scanf cu adresa lor.
  if (strcmp(l.tip_locuinta, "garsoniera") == 0) {
    short unsigned balcon = 0;
    sscanf(line, "%hu", &balcon);
    l.info.balcon = balcon;
  } else if (strcmp(l.tip_locuinta, "apartament") == 0) {
    char decomandat;
    sscanf(line, "%c", &decomandat);
    l.info.decomandat = decomandat;
  } else if (strcmp(l.tip_locuinta, "casa") == 0) {
    char casa_info[30];
    memset(casa_info, 0, sizeof(casa_info));
    sscanf(line, "%30s", casa_info);
    strcpy(l.info.casa_info, casa_info);
  } else {
    printf("Tip locuinta %s inexistent!\n", l.tip_locuinta);
    exit(-1);
  }

  return l;
}

void pretty_print_locuinta(Locuinta l) {
  printf("Locuinta la adresa %s cu suprafata %.2f de tipul %s cu %d camere si ",
         l.adresa, l.suprafata, l.tip_locuinta, l.numar_camere);

  if (strcmp(l.tip_locuinta, "garsoniera") == 0) {
    if (l.info.balcon == 1)
      printf("cu balcon\n");
    else
      printf("fara balcon\n");
  } else if (strcmp(l.tip_locuinta, "apartament") == 0) {
    if (l.info.decomandat == 'D')
      printf("decomandat\n");
    else
      printf("nedecomandat\n");
  } else if (strcmp(l.tip_locuinta, "casa") == 0) {
    printf("%s\n", l.info.casa_info);
  }
}

int index_garsoniera_max_balcon(Locuinta loc[], int num_loc) {
  int idx_garsoniera = -1;
  float max_suprafata_garsoniera = 0;
  for (int i = 0; i < num_loc; i++) {
  	if (strcmp(loc[i].tip_locuinta, "garsoniera") == 0) {
  		printf("Idx %d is garsoniera and balcon is %hu\n", i, loc[i].info.balcon);
  		if (loc[i].info.balcon && loc[i].suprafata > max_suprafata_garsoniera) {
  			max_suprafata_garsoniera = loc[i].suprafata;
  			idx_garsoniera = i;
  		}
  	}
  }
  return idx_garsoniera;
}