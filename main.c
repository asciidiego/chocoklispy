#ifdef __APPLE__
char* __PLATFORM__ = "Mac";
#elif defined __linux__
char* __PLATFORM__ = "Linux";
#else
char* __PLATFORM__ = "Windows";
#endif

#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>


int main(int argc, char** argv) {
  // Print version and exit info
  puts("Chococlispy version 0.0.0.0.3");
  puts("Press Ctrl + C to exit.");
  printf("Platform: %s\n\n", __PLATFORM__);

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
