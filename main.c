#include <stdio.h>


// Declare a buffer for user input of size 2048
static char input[2048];


int main(int argc, char** argv) {
  // Print version and exit info
  puts("Chococlispy version 0.0.0.0.1");
  puts("Press Ctrl + C to exit.\n");

  while (1) {
    // Output our prompt
    fputs("chococlispy> ", stdout);

    // Read a userline (max size of 2048)
    fgets(input, 2048, stdin);

    // Echoes input back
    printf("%s", input);
  }

  return 0;
}
