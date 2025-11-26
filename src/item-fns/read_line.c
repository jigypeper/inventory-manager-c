#include <stdio.h>
#include <ctype.h>
#include "read_line.h"

int read_line(char str[], int n) {
  int ch, i = 0;
  // clearing any leading spaces
  while (isspace(ch = getchar()));

  // reading until spaces and EOF
  while (ch != ' ' && ch != EOF) {
    if (i < n) {
      str[i++] = ch;
    }
    ch = getchar();
  }
  str[i] = '\0';
  return i;
}
