#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

	/*        bla bla
   comentariul asta e folosit doar pentru test */

/* alt comentariu
   pe
   mai
   multe 
   linii
   */

int check_closed_multiline_comment(const char* line) {
	int n = strlen(line);

	// Gasesc ultimele caractere diferite de spatiu de pe linie.
	int j = n - 1;
	while (j >= 0 && isspace(line[j])) j--;

	// Daca ultimele 2 caractere diferite de spatiu sunt "*/", 
	// inseamna ca s-a incheiat comentariul pe mai multe linii.
	if (line[j] == '/' && (j >= 1) && (line[j - 1] == '*')) {
		return 1;
	}

	return 0;
}

// Facem o presupunere simplificatoare:
// un comentariu ocupa mereu intreaga linie 
// (deci nu exista situatii de genul:
// int x;   // bla bla bla
//    sau
// int X;    /*  comentariu pe 
//   mai multe linii */ 
// ))
void read_and_remove_comments(const char* file_name) {
	// Deschid fisierul in mod citire (implicit text)
	FILE* f = fopen(file_name, "r");
	if (f == NULL) {
		fprintf(stderr, "Nu am putut deschide fisierul %s pentru citire\n", file_name);
		exit(-1);
	}

	// Dimensiunea maxima a unei linii din fisier.
	const int max_dim = 1024;
	char line[max_dim];
	int multiple_line_comment_found = 0;

	// Din documentatia lui fgets():
	// fgets() returns s on success, and NULL on error or when end
	// of file occurs  while  no  characters  have been read.
	while (fgets(line, max_dim, f) != NULL) {
		// Gasesc prima pozitie din sirul line unde nu este un whitespace
		// (spatiu, tab, newline etc)
		int i = 0, n = strlen(line);
		while ((i < n) && isspace(line[i])) i++;

		// Un comentariu (fie el simplu // sau pe mai multe linii /* ... */, 
		// incepe cu caracterul '/' ), deci daca primul caracter nu e '/', 
		// linia nu e comentariu (decat daca suntem in mijlocul unui comentariu
		// pe mai multe linii), deci o printez
		if (line[i] != '/') {
			if (!multiple_line_comment_found) {
				printf("%s", line);
			} 
			// Altfel, daca sunt in mijlocul unui comentariu pe mai multe linii, 
			// trebuie sa verific daca exista "*/" la finalul liniei
			else {
				int is_closed = check_closed_multiline_comment(line);
				if (is_closed) {
					multiple_line_comment_found = 0;
				}
			}
		}

		// Comentariu simplu ("//")
		if ((i + 1 < n) && line[i + 1] == '/') continue;

		// Comentariu pe mai multe linii ("/*...")
		if ((i + 1 < n) && line[i + 1] == '*') {
			multiple_line_comment_found = 1;

			// Este posibil ca un comentariu pe mai multe lini sa se incheie
			// chiar pe linia pe care a inceput, deci verific daca ultimele 
			// caractere diferite de spatiu din linie sunt "*/"
			int is_closed = check_closed_multiline_comment(line);
			if (is_closed) multiple_line_comment_found = 0;
		}
	}

	fclose(f);
}

int main() {
	/* Exercitiul poate fi testat chiar pe sursa aceasta */
	read_and_remove_comments("ex3.c"); 
}