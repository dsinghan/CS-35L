#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int frobcmp(char const *x, char const *y) { //compare the two frobnicated strings
	while (*x == *y) { //checks to see if they are the same until x hits the space
		if (*x == ' ') {
			return 0;
		}
		x++;
		y++;
	}

	char X = *x ^ 42; //convert from frobnicated form
	char Y = *y ^ 42;

	if (Y > X || *x == ' ') { //checks to see if x is smaller
		return -1;
	}
	else if (X > Y || *y == ' ') { //checks to see if x is bigger
		return 1;
	}
}

int fq(const void *x, const void *y) { //run frobcmp within qsort, since frobcmp doesn't work directly
	const char *X = *(const char**)x;
	const char *Y = *(const char**)y;
	return frobcmp(X, Y);
}

void test(ssize_t x) { //check for valid input
	if (x == -1) {
		fprintf(stderr, "Invalid Input");
		exit(1);
	}
}

int main(int argc, char **argv) {

	char *a = (char*)malloc(sizeof(char)); //define a as current char and b as its pointer
	char **b = (char**)malloc(sizeof(char*));

	if (a == NULL || b == NULL) { //check if they're null
		fprintf(stderr, "Invalid Memory");
		exit(1);
	}

	int c = 0; //length of arrays
	int d = 0;
	char e; //current char
	char* f = &e; //pointer to current char

	int g = 1; //holds char validity
	while (g != 0) { //checks next char until eof
		g = read(STDIN_FILENO, f, 1); //get next character
		test(g); //check output

		if (c > 0 && (g == 0 || e == ' ')) { //if end of output is reached
			a = (char*)realloc(a, (c + 1) * sizeof(char)); //allocate space
			a[c] = ' '; //add space at the end

			char *h = (char*)malloc(sizeof(char)); //begin next word
			b = (char**)realloc(b, (d + 1) * sizeof(char*));

			if (h != NULL && b != NULL) { //error test
				b[d] = a;
				d++;
				a = h;
				c = 0;
			}

			else {
				fprintf(stderr, "Invalid Memory");
				free(a);
				exit(1);
			}
		}

		else {
			a = (char*)realloc(a, (c + 1) * sizeof(char)); //allocate space

			if (a != NULL) { //error test
				a[c] = e;
				c++;
			}

			else {
				fprintf(stderr, "Invalid Memory");
				exit(1);
			}
		}
	}

	qsort(b, d, sizeof(char*), fq); //use qsort

	for (int x = 0; x < d; x++) { //print everything out
		for (int y = 0; b[x][y] != '\0'; y++) {
			if (b[x][y] == '\0') {
				break;
			}

			g = write(STDOUT_FILENO, &b[x][y], 1); //do the test
			test(g);
			if (b[x][y] == ' ') {
				break;
			}
		}
	}

	for (int x = 0; x < d; x++) { //deallocate the memory
		free(b[x]);
	}
	free(b);
	free(a);

	exit(0);
}
