#include <stdio.h>
#include <stdlib.h>
#include <float.h>	// pentru DBL_MAX
#include <math.h> 	// !! pe linux trebuie compilat cu -lm

typedef struct Complex {
	double real;
	double imag;
} Complex;

double abs_val(const Complex c) {
	return sqrt(c.real * c.real + c.imag * c.imag);
}

// Intorc indexul numarului complex din array-ul arr_complex
// care are cel mai mare modul
int get_complex_max_abs_val(int n, Complex *arr_complex) {
	double max_abs = -DBL_MAX;		// modulul maxim
	int idx_max_abs_val = -1;		// indexul elem cu modul maxim

	for (int i = 0; i < n; i++) {
		double crt_abs_val = abs_val(arr_complex[i]);
		if (crt_abs_val > max_abs) {
			max_abs = crt_abs_val;
			idx_max_abs_val = i;
		}
	}

	return idx_max_abs_val;
}

int main() {
	int n;
	scanf("%d", &n);

	Complex *arr_complex = (Complex*)calloc(n, sizeof(Complex));
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &arr_complex[i].real, &arr_complex[i].imag);
	}

	int idx = get_complex_max_abs_val(n, arr_complex);
	if (idx != -1) {
		printf("Numarul complex cu cel mai mare modul este: (%.2lf)+(%.2lf)i\n", 
			arr_complex[idx].real, arr_complex[idx].imag);
	} else {
		printf("Nu am gasit niciun numar in arr_complex.\n");
	}

	// Dealocare memorie
	free(arr_complex);
}