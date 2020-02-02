%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  int quit;
  double value;
  const char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"
%token <sin>      SIN         "sin"
%token <cos>      COS         "cos"
%token <tan>      TAN         "tan"
%token <sqrt>     SQRT        "sqrt"
%token <random>   RANDOM      "random"

%token <quit>     QUIT        "quit"
%token            COLOR       "color"
%token            KW_FORWARD  "forward"

/* TODO: add other tokens */

%left '^'
%left '+' '-'
%left '*' '/'

%type <node> unit cmds cmd expr

%%

unit:
    cmds                      { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds                  { $1->next = $2; $$ = $1; }
  | /* empty */               { $$ = NULL; }
;

cmd:
    KW_FORWARD expr '\n'      { $$ = make_cmd_forward($2); }
  | QUIT '\n'                 { make_cmd_quit(); /*printf("Application close\n"); exit(0);*/ }
  | COLOR expr '\n'           { $$ = make_cmd_color_from_keyword($2); }
  | COLOR expr expr expr '\n' { $$ = make_cmd_color_from_expr($2, $3, $4); }
  | expr '\n'                 { printf("expr >>\n"); }
;

expr:
    VALUE                     { $$ = make_expr_value($1); }
  | NAME                      { printf(">> Name\n"); }
  | expr '+' expr             { $$ = make_expr_binary_op('+', $1, $3); }
  | expr '-' expr             { $$ = make_expr_binary_op('-', $1, $3); }
  | expr '*' expr             { $$ = make_expr_binary_op('*', $1, $3); }
  | expr '/' expr             { $$ = make_expr_binary_op('/', $1, $3); }
  | expr '^' expr             { $$ = make_expr_binary_op('^', $1, $3); }
  | '(' expr ')'              { $$ = make_expr_block('(', ')', $2); }
  | '-' expr                  { $$ = make_expr_unary_op('-', $2); }
  | SIN '(' expr ')'          { $$ = make_expr_func(FUNC_SIN, $3, NULL); }
  | COS '(' expr ')'          { $$ = make_expr_func(FUNC_COS, $3, NULL); }
  | TAN '(' expr ')'          { $$ = make_expr_func(FUNC_TAN, $3, NULL); }
  | SQRT '(' expr ')'         { $$ = make_expr_func(FUNC_SQRT, $3, NULL); }
  | RANDOM '(' expr ',' expr ')'    { $$ = make_expr_func(FUNC_RANDOM, $3, $5); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
