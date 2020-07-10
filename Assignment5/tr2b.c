#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int a, char *b[]){ //a is # of args and b contains args
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

  char e = getchar(); //define e as current char

  while (!feof(stdin)){
    for (int x = 0; x < c; x++){
      if (e == from[x]){ //if e is in from, replace with to
	e = to[x];
	break;
      }
    }
    putchar(e); //otherwise keep the same
    e = getchar();
  }

  return 0;
}
