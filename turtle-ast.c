#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

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
  node->children_count = 0;
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

struct ast_node *make_cmd_backward(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_up(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_down(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 2;
  node->children[0] = expr1;
  node->children[1] = expr2;
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
  if(self!=NULL){
    struct ast_node * root = self->unit;
    freeNode(root);
  };
}

void freeNode(struct ast_node *self){
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

/* Evaluation of the commands */
// struct ast_node * ast_eval_cmd(const struct ast_node *self)
// {
//   switch (self->kind) {
//     case KIND_CMD_SIMPLE:
//       return ast_eval_cmd_simple(self);
//       break;
//   }
// }
//
// /* Evaluation of the commands */
// struct ast_node * ast_eval_cmd_simple(const struct ast_node *self)
// {
//   switch (self->u.cmd) {
//     case CMD_COLOR:
//       return
//       break;
//   }
// }

/* Evaluation of the expressions */
struct ast_node * ast_eval_expr(const struct ast_node *self)
{
  return make_expr_value(ast_eval_expr_value(self));
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

void ast_print(const struct ast *self)
{
  if(self!=NULL) {
    struct ast_node * root = self->unit;
    print_node(root);
  }
}

void print_node(struct ast_node *self)
{
  if(self!=NULL)
  {

    int parentheses = false; //Boolean
    int accolade = false; //Boolean
    int comma = false; //Boolean

    switch (self->kind) {
      case KIND_CMD_SET:
        printf("set ");
        break;
      case KIND_CMD_CALL:
        printf("call ");
        break;
      case KIND_CMD_PROC:
        printf("proc ");
        break;
      case KIND_CMD_BLOCK:
        accolade = true;
        printf("{ ");
        break;
      case KIND_CMD_REPEAT:
        printf("repeat ");
        break;
      case KIND_CMD_SIMPLE:
        switch (self->u.cmd) {
          case CMD_DOWN:
            printf("down ");
            break;
          case CMD_UP:
            printf("up ");
            break;
          case CMD_LEFT:
            printf("left ");
            break;
          case CMD_RIGHT:
            printf("right ");
            break;
          case CMD_FORWARD:
            printf("fw ");
            break;
          case CMD_BACKWARD:
            printf("bw ");
            break;
          case CMD_HOME:
            printf("home ");
            break;
          case CMD_PRINT:
            printf("print ");
            break;
          case CMD_COLOR:
            printf("color ");
            break;
          case CMD_HEADING:
            printf("heading ");
            break;
          case CMD_POSITION:
            printf("pos ");
            break;
        }
        break;

      case KIND_EXPR_FUNC:
        switch (self->u.func) {
          case FUNC_COS:
            printf("cos( ");
            parentheses = true;
            break;
          case FUNC_SIN:
            printf("sin( ");
            parentheses = true;
            break;
          case FUNC_TAN:
            printf("tan( ");
            parentheses = true;
            break;
          case FUNC_SQRT:
            printf("sqrt( ");
            parentheses = true;
            break;
          case FUNC_RANDOM:
            printf("random( ");
            parentheses = true;
            comma = true;
            break;
        }
        break;
      case KIND_EXPR_NAME:
        printf("%s", self->u.name);
        break;
      case KIND_EXPR_UNOP:
      case KIND_EXPR_BINOP:
        printf("%d", self->u.op);
      case KIND_EXPR_BLOCK:
        break;
      case KIND_EXPR_VALUE:
        printf("%f", self->u.value);
        break;
    }

    for(int i=0; i<self->children_count; ++i) {
      print_node(self->children[i]);
      if(comma == true) {
        printf(", ");
        comma = false;
      }
    }

    if(parentheses == true) {
      printf(" ) ");
      parentheses = false;
    }
    if(accolade == true) {
      printf("} ");
      accolade = false;
    }

    if(self->kind == KIND_CMD_SET || self->kind == KIND_CMD_CALL || self->kind == KIND_CMD_PROC || self->kind == KIND_CMD_BLOCK || self->kind == KIND_CMD_REPEAT || self->kind == KIND_CMD_SIMPLE) {
      printf("\n");
    }

    print_node(self->next);
  }
}
