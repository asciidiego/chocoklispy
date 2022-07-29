#ifdef __APPLE__
char *__PLATFORM__ = "Mac";
#elif defined __linux__
char *__PLATFORM__ = "Linux";
#else
char *__PLATFORM__ = "Windows";
#endif

#define DEBUG false

#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

#include "mpc.h"

double eval_op(char* op, double x, double y) {
  if (strcmp(op, "+") == 0) {
    return x + y;
  }
  if (strcmp(op, "-") == 0) {
    return x - y;
  }
  if (strcmp(op, "*") == 0) {
    return x * y;
  }
  if (strcmp(op, "/") == 0) {
    return x / y;
  }
  return 0;
}


double eval(mpc_ast_t* ast) {
  // if number, simply return it
  if (strstr(ast->tag, "number")) {
    return atof(ast->contents);
  }

  // the first child is "(" always; we can skip it.
  char* operator = ast->children[1]->contents;

  // like with reduce, we start with the first child...
  double accum = eval(ast->children[2]);

  // ... and iterate with the remaining children
  int i = 3;
  while (strstr(ast->children[i]->tag, "expr")) {
    accum = eval_op(operator, accum, eval(ast->children[i]));
    i++;
  }

  return accum;
}


int main(int argc, char **argv)
{
  // Create some parsers
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Chocoklispy = mpc_new("chocoklispy");

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
  char* VERSION = "0.0.0.0.4";
  printf("Chocoklispy version %s\n", VERSION);
  puts("Press Ctrl + C to exit.");
  printf("Platform: %s\n\n", __PLATFORM__);

  while (1)
  {
    // output our prompt
    char *input = readline("chocoklispy> ");

    // add input to history
    add_history(input);

    // parsing result
    mpc_result_t result;

    if (mpc_parse("<stdin>", input, Chocoklispy, &result))
    {
      #if DEBUG
      mpc_ast_print(result.output);
      #endif

      double eval_result = eval(result.output);
      printf("%f\n", eval_result);
      mpc_ast_delete(result.output);
    }
    else
    {
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
