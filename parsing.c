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

#include "mpc.h"


int main(int argc, char** argv) {
    // Create some parsers
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Chocoklispy = mpc_new("chocoklispy");

    // Define chocoklispy language
    mpca_lang(MPCA_LANG_DEFAULT,
	    "\
	    number: /-?[0-9]+[.][0-9]+/ | /-?[0-9]+/  ; \
	    operator: '+' | '-' | '*' | '/' ; \
	    expr: <number> | '(' <operator> <expr>+ ')' ; \
	    chocoklispy: /^/ <operator> <expr>+ /$/ ;\
	    ",
	    Number, Operator, Expr, Chocoklispy);

  // Print version and exit info
  puts("Chocoklispy version 0.0.0.0.3");
  puts("Press Ctrl + C to exit.");
  printf("Platform: %s\n\n", __PLATFORM__);

  while (1) {
    // output our prompt
    char* input = readline("chocoklispy> ");

    // add input to history
    add_history(input);

    // echo input back
    mpc_result_t result;

    if (mpc_parse("<stdin>", input, Chocoklispy, &result)) {
      mpc_ast_print(result.output);
      mpc_ast_delete(result.output);
    } else {
      mpc_err_print(result.error);
      mpc_err_delete(result.error);
    }

    // free memory
    free(input);
  }


  // undefine and delete parsers
  mpc_cleanup(4, Number, Operator, Expr, Chocoklispy);
  
  return 0;
}
