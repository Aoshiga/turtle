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

struct ast_node *make_expr_block(char lhs, char rhs, struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BLOCK;
  node->children_count = 1;
  node->children[0] = expr;
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

/*void *make_cmd_quit(struct ast_node * self)
{
  // TO DO - - - - destroy before quit
  if(self!=NULL)
    freeNode(self);
  self = NULL;
  return self;
}*/


void ast_destroy(struct ast *self) {
  printf("hello1");
  if(self!=NULL){
    struct ast_node * root = self->unit;
    freeNode(root);
  };

}

void freeNode(struct ast_node *self){
    printf("hello2");

  if(self!=NULL){
    for(int i =0;i<self->children_count;++i){
      freeNode(self->children[i]);
    }
    freeNode(self->next);
    free(self);
    self = NULL;
  }
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
      switch (self->u.op) {
        case '+' :
          return ast_eval_expr_value(self->children[0]) + ast_eval_expr_value(self->children[1]);
          break;
        case '-' :
          return ast_eval_expr_value(self->children[0]) - ast_eval_expr_value(self->children[1]);
          break;
        case '*' :
          return ast_eval_expr_value(self->children[0]) * ast_eval_expr_value(self->children[0]);
          break;
        case '/' :
          return ast_eval_expr_value(self->children[0]) / ast_eval_expr_value(self->children[1]);
          break;
      }
      break;
    default:
      return 0;
      break;
  }

  return 0;
}


/*
 * print
 */

void ast_print(const struct ast *self) {

}
