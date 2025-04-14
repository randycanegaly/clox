#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char *source) {
  initScanner(source);
  int line = 1;
  for (;;) {
    Token token = scanToken(); // get one token
    if (token.line != line) { // this token is on a different line in the source
                              // code so print the new line number
      printf("%4d ", token.line); // integer, printed in a field 4 places wide
      line = token.line; // set the line tracker variable to the new line number
    } else {
      printf("  | "); // the token is on the same line as the token before so
                      // print the 'same line' marker
    }
    printf("%2d '%.*s'\n", token.type, token.length,
           token.start); // print out a description of the token scanner
    // integer 2 characters wide, string of max length token.length as pointed
    // to by token.start

    if (token.type ==
        TOKEN_EOF) // break out of the loop if end of file is reached
      break;
  }
}
