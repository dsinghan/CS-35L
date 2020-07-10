#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test (ssize_t x) { //checks for invalid inputs
  if (x != 0 && x == -1) {
    fprintf(stderr, "Invalid input");
    exit(1);
  }
}

int main (int a, char *b[]) { //a is # of args and b contains args
  if (a != 3){ //check for exactly three args
    fprintf(stderr, "Invalid # of args");
    exit(1);
  }
  
  char *from = b[1]; //define args as from and to
  char *to = b[2];

  int c = strlen(from); //define c and d as length of args
  int d = strlen(to);

  if (c != d){ //check for same length
    fprintf(stderr, "from and to are different lengths");
    exit(1);
  }

  for (int x = 0; x < c; x++){
    for (int y = x + 1; y < c; y++){
      if (from[x] == from[y]){ //check for duplicate chars
	fprintf(stderr, "from has duplicate bytes");
	exit(1);
      }
    }
  }

  char e; //define current char and pointer to it
  char *f = &e; //get stdin and check in from
  ssize_t g = read(STDIN_FILENO, f, 1);
  test(g); //check the input
  
  while (g != 0) { //loop through the input
    for (int x = 0; x < c; x++) {
      if (e == from[x]) {
	e = to[x];
	break;
      }
    }
    write(STDOUT_FILENO, f, 1); //do the check
    g = read(STDIN_FILENO, f, 1);
    test(g);
  }
  
  return 0;
}
