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
%token            KW_BACKWARD "backward"
%token            KW_UP       "up"
%token            KW_DOWN     "down"
%token            KW_POSITION "position"
%token            KW_RIGHT    "right"
%token            KW_LEFT     "left"

%token            PRINT       "print"



/* TODO: add other tokens */

%left '+' '-'
%left '*' '/'
%left '^'
%precedence NEG
%left '('

%type <node> unit cmds cmd expr

%%

unit:
    cmds                      { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds                  { $1->next = $2; $$ = $1; }
  | /* empty */               {$$ = NULL; }

;

cmd:
    KW_FORWARD expr           { $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr          { $$ = make_cmd_backward($2); }
  | KW_UP expr                { $$ = make_cmd_up($2); }
  | KW_DOWN expr              { $$ = make_cmd_down($2); }
  | KW_RIGHT expr             { $$ = make_cmd_right($2); }
  | KW_LEFT expr              { $$ = make_cmd_left($2); }
  | KW_POSITION expr expr     { $$ = make_cmd_position($2, $3); }
  | COLOR expr                { $$ = make_cmd_color_from_keyword($2); }
  | COLOR expr expr expr      { $$ = make_cmd_color_from_expr($2, $3, $4); }
  | PRINT expr                { $$ = make_cmd_print($2); }
;

expr:
    VALUE                     { $$ = make_expr_value($1); }
  | NAME                      { $$ = make_expr_color($1); } /* ----- change it later */
  | expr '+' expr             { $$ = make_expr_binary_op('+', $1, $3); }
  | expr '-' expr             { $$ = make_expr_binary_op('-', $1, $3); }
  | expr '*' expr             { $$ = make_expr_binary_op('*', $1, $3); }
  | expr '/' expr             { $$ = make_expr_binary_op('/', $1, $3); }
  | expr '^' expr             { $$ = make_expr_binary_op('^', $1, $3); }
  | '(' expr ')'              { $$ = $2; }
  | '-' expr %prec NEG        { $$ = make_expr_unary_op('-', $2); }
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
