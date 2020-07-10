#include <stdio.h>
#include <stdlib.h>

//compare the two frobnicated strings
int frobcmp (char const *x, char const *y){
  while (*x == *y){ //checks to see if they are the same until x hits the space
    if (*x == ' '){
      return 0;
    }
    x++;
    y++;
  }
  
  char X = *x ^ 42; //convert from frobnicated form
  char Y = *y ^ 42;

  if (Y > X || *x == ' '){ //checks to see if x is smaller
    return -1;
  }
  else if (X > Y || *y == ' '){ //checks to see if x is bigger
    return 1;
  }
}

//run frobcmp within qsort, since frobcmp doesn't work directly
int fq (const void *x, const void *y){
  const char *X = *(const char**)x;
  const char *Y = *(const char**)y;
  return frobcmp(X, Y);
}

int main(){
  char *x = (char*) malloc(sizeof(char*)); //will ultimately contain stdin

  int a = 0; //a is index of chars and b is index of words
  int b = 0;
  char c = getchar(); //c is current char
  
  if (x == NULL){ //checks if stdin is valid
    fprintf(stderr, "Memory Error");
    exit(1);
  }

  while (c != EOF){ //read stdin into x
    if (c == ' '){
      if (a != 0){
	if (x[a - 1] != ' '){ //if c is a space, read it into x and increment one for b
	  x[a] = c;
	  b++;
	}
      }
    }
    else{ //otherwise read it into x and don't increment b
      x[a] = c;
    }
    
    x = (char*) realloc(x, sizeof(char*) *(a + 1)); //resize c for other chars
    if (x == NULL){ //make sure it isn't null
      fprintf(stderr, "Memory Error");
      exit(1);
    }
    a++; //increment and get next char
    c = getchar();
  }
  
  if (c == EOF){ //at end of file make sure a has incremented and add a space if last character isn't
    if (a == 0){
      fprintf(stderr, "Input Error");
      exit(1);
    }
    if (a - 1 != ' '){
      x[a] = ' ';
      b++;
    }
  }

  char **d = (char**) malloc(sizeof(char*) *b); //make space for d which points to the various words
  char *e = x; //e points to x
  
  if (d == NULL){ //make sure the pointer to words aren't null
    fprintf(stderr, "Memory Error");
    exit(1);
  }
  
  int i = 0;
  int j = 0; //define iterators i and j

  for (int i = 0; i < b; i++){ //put words from x into d
    d[i] = e;
    if (i + 1 == b){
      break;
    }
    while (*e != ' '){
      e++;
    }
    e++;
  }

  qsort(d, b, sizeof(char*), fq); //sort the words from stdin

  while (i < b){ //print all the characters from each word from d
    while (j < a){
      putchar(d[i][j]);
      if (d[i][j] == ' '){
	break;
      }
      j++;
    }
    i++;
  }

  free(x); //deallocate the memory
  free(d);
  exit(0);
}
