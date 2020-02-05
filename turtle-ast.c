#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

/*
 * expressions
 */
struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->children_count = 0; /// <--------------- Implement this, wasn't here at the beginning (comment writing for the report)
  node->u.value = value;
  return node;
}

struct ast_node *make_expr_binary_op(char op, struct ast_node *expr1, struct ast_node *expr2)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BINOP;
  node->u.op = op;
  node->children_count = 2;
  node->children[0] = expr1;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_expr_unary_op(char op, struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_UNOP;
  node->u.op = op;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_func(enum ast_func func, struct ast_node *expr1, struct ast_node *expr2)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.func = func;
  if(expr2 == NULL)
  {
    node->children_count = 1;
    node->children[0] = expr1;
  } else {
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
  }
  return node;
}

struct ast_node *make_expr_color(const char *name)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->u.name = name;
  return node;
}

/*
 * commands
 */
struct ast_node *make_cmd_color_from_expr(struct ast_node *red, struct ast_node *green, struct ast_node *blue)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  node->children[0] = red;
  node->children[1] = green;
  node->children[2] = blue;
  return node;
}

struct ast_node *make_cmd_color_from_keyword(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

void *make_cmd_quit()
{
  // TO DO - - - - destroy before quit
  exit(0);
}


void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {

}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

void ast_eval_expr(const struct ast_node *self)
{
  printf(">> %f\n", ast_eval_expr_value(self));
}

double ast_eval_expr_value(const struct ast_node *self)
{
  switch (self->kind) {
    case KIND_EXPR_VALUE:
      return self->u.value;
      break;
    case KIND_EXPR_BINOP:
      return ast_eval_expr_value_op(self);
      break;
    case KIND_EXPR_UNOP:
      return -ast_eval_expr_value(self->children[0]);
      break;
    case KIND_EXPR_FUNC:
      return ast_eval_expr_value_func(self);
    default:
      return 0;
      break;
  }
}

double ast_eval_expr_value_op(const struct ast_node *self)
{
  double x = ast_eval_expr_value(self->children[0]);
  double y = ast_eval_expr_value(self->children[1]);
  switch (self->u.op) {
    case '+' :
      return x+y;
      break;
    case '-' :
      return x-y;
      break;
    case '*' :
      return x*y;
      break;
    case '/' :
      if(y == 0) {
        printf("Error : Division by zero\n");
        exit(1); // ERROR Division by 0 is forbiden                                //// TO DO exit //////
      }
      return x/y;
      break;
    case '^' :
      return pow(x,y);
    default :
      return 0;
      break;
  }
}

double ast_eval_expr_value_func(const struct ast_node *self)
{
  double x = ast_eval_expr_value(self->children[0]);
  switch (self->u.func) {
    case FUNC_SIN :
      return sin(x);
      break;
    case FUNC_COS :
      return cos(x);
      break;
    case FUNC_TAN :
      return tan(x);
      break;
    case FUNC_SQRT :
      if(x < 0) {                                                                 /// TO DO ////////////
        printf("Error : Sqrt of negative number\n");
        exit(1); // ERROR sqrt must to be positive
      }
      return sqrt(x);;
      break;
    case FUNC_RANDOM :
      {int min = (int)x;
      int max = (int)ast_eval_expr_value(self->children[1]);
      return (rand()%(max-min+1)+min);}
      break;
    default :
      return 0;
      break;
  }
}

/*
 * print
 */

void ast_print(const struct ast *self) {

}
