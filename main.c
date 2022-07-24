#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>


int main(int argc, char** argv) {
  // Print version and exit info
  puts("Chococlispy version 0.0.0.0.2");
  puts("Press Ctrl + C to exit.\n");

  while (1) {
    // output our prompt
    char* input =  readline("chococlispy> ");

    // add input to history
    add_history(input);

    // echo input back
    printf("%s\n", input);

    // free memory
    free(input);
  }

  return 0;
}
