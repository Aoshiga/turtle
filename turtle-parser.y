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
  double value;
  char *name;
  struct ast_node *node;
}

%token <name>     NAME        "name"
%token <value>    VALUE       "value"
%token <cos>      COS         "cos"
%token <sin>      SIN         "sin"
%token <tan>      TAN         "tan"
%token <sqrt>     SQRT        "sqrt"
%token <random>   RANDOM      "random"

%token            KW_UP       "up"
%token            KW_DOWN     "down"
%token            KW_RIGHT    "right"
%token            KW_LEFT     "left"
%token            KW_HEADING  "heading"
%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_POSITION "position"
%token            KW_HOME     "home"
%token            KW_COLOR    "color"
%token            KW_PRINT    "print"

%token            REPEAT      "repeat"
%token            SET         "set"
%token            PROC        "proc"
%token            CALL        "call"

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
    KW_UP                           { $$ = make_cmd_up(); }
  | KW_DOWN                         { $$ = make_cmd_down(); }
  | KW_RIGHT expr                   { $$ = make_cmd_right($2); }
  | KW_LEFT expr                    { $$ = make_cmd_left($2); }
  | KW_HEADING expr                 { $$ = make_cmd_heading($2); }
  | KW_FORWARD expr                 { $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr                { $$ = make_cmd_backward($2); }
  | KW_POSITION expr ',' expr       { $$ = make_cmd_position($2, $4); }
  | KW_HOME                         { $$ = make_cmd_home(); }
  | KW_COLOR expr                   { $$ = make_cmd_color_from_keyword($2); }
  | KW_COLOR expr ',' expr ',' expr { $$ = make_cmd_color_from_expr($2, $4, $6); }
  | KW_PRINT expr                   { $$ = make_cmd_print($2); }
  | '{' cmds '}'                    { $$ = make_cmd_block($2); } /* BLOCK */
  | REPEAT expr cmd                 { $$ = make_cmd_repeat($2, $3); }
  | SET expr expr                   { $$ = make_cmd_set($2, $3); }
  | PROC expr cmd                   { $$ = make_cmd_proc($2, $3); }
  | CALL expr                       { $$ = make_cmd_call($2); }
;

expr:
    VALUE                           { $$ = make_expr_value($1); }
  | NAME                            { $$ = make_expr_name($1); }
  | expr '+' expr                   { $$ = make_expr_binary_op('+', $1, $3); }
  | expr '-' expr                   { $$ = make_expr_binary_op('-', $1, $3); }
  | expr '*' expr                   { $$ = make_expr_binary_op('*', $1, $3); }
  | expr '/' expr                   { $$ = make_expr_binary_op('/', $1, $3); }
  | expr '^' expr                   { $$ = make_expr_binary_op('^', $1, $3); }
  | '(' expr ')'                    { $$ = $2; }
  | '-' expr %prec NEG              { $$ = make_expr_unary_op('-', $2); }
  | SIN '(' expr ')'                { $$ = make_expr_func(FUNC_SIN, $3, NULL); }
  | COS '(' expr ')'                { $$ = make_expr_func(FUNC_COS, $3, NULL); }
  | TAN '(' expr ')'                { $$ = make_expr_func(FUNC_TAN, $3, NULL); }
  | SQRT '(' expr ')'               { $$ = make_expr_func(FUNC_SQRT, $3, NULL); }
  | RANDOM '(' expr ',' expr ')'    { $$ = make_expr_func(FUNC_RANDOM, $3, $5); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
