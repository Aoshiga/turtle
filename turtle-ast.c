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

struct ast_node *make_expr_color(char *name)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->children_count = 0;
  node->u.name = name;
  return node;
}

/*
 * Simple commands
 */
struct ast_node *make_cmd_up()
{
 struct ast_node *node = calloc(1, sizeof(struct ast_node));
 node->kind = KIND_CMD_SIMPLE;
 node->u.cmd = CMD_UP;
 node->children_count = 0;
 return node;
}

struct ast_node *make_cmd_down()
{
 struct ast_node *node = calloc(1, sizeof(struct ast_node));
 node->kind = KIND_CMD_SIMPLE;
 node->u.cmd = CMD_DOWN;
 node->children_count = 0;
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

struct ast_node *make_cmd_heading(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
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

struct ast_node *make_cmd_home()
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  node->children_count = 0;
  return node;
}

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

struct ast_node *make_cmd_print(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

/*
 * Other commands
 */
struct ast_node *make_cmd_block(struct ast_node *cmd)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_BLOCK;
  node->children_count = 1;
  node->children[0] = cmd;
  return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_REPEAT;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = cmd;
  return node;
}

/**
* Delete all the node at the end of the programm
*/
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
  self->x = 0;
  self->y = 0;
  self->angle = -90;
  self->up = false;
  self->color = "black";
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
  if(self!=NULL)
  {
    struct ast_node * root = self->unit;
    ast_eval_cmd(root, ctx);
  }
}

/* Evaluation of the commands */
void ast_eval_cmd(const struct ast_node *self, struct context *ctx)
{
  int loop;
  if(self!=NULL)
  {
    switch (self->kind) {
      case KIND_CMD_SIMPLE:
        ast_eval_cmd_simple(self, ctx);
        break;
      case KIND_CMD_BLOCK:
        ast_eval_cmd(self->children[0], ctx);
        break;
      case KIND_CMD_REPEAT:
        loop = floor(ast_eval_expr(self->children[0]));
        for(int i=0; i<loop; ++i) {
          ast_eval_cmd(self->children[1], ctx);
        }
        break;
      default:
        break;
    }

    ast_eval_cmd(self->next, ctx);
  }


}

/* Evaluation of the simple commands */
void ast_eval_cmd_simple(const struct ast_node *self, struct context *ctx)
{
  switch (self->u.cmd) {
    case CMD_FORWARD:
      ctx->x += cos(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0]);
      ctx->y += sin(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0]);
      if(!ctx->up){
        printf("LineTo %f %f", ctx->x, ctx->y);
      }
      break;
    case CMD_BACKWARD:
      ctx->x -= cos(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0]);
      ctx->y -= sin(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0]);
      if(!ctx->up){
        printf("LineTo %f %f", ctx->x, ctx->y);
      }
      break;
    case CMD_POSITION:
      ctx->x = ast_eval_expr(self->children[0]);
      ctx->y = ast_eval_expr(self->children[1]);
      printf("MoveTo %f %f", ctx->x, ctx->y);
      break;
    case CMD_RIGHT:
      ctx->angle += ast_eval_expr(self->children[0]);
      break;
    case CMD_LEFT:
      ctx->angle -= ast_eval_expr(self->children[0]);
      break;
    case CMD_HEADING:
      ctx->angle = ast_eval_expr(self->children[0])-90; //-90 cause 0 must to be the north -- in turtle-viewer, the north is -90
      break;
    case CMD_UP:
      ctx->up = true;
      break;
    case CMD_DOWN:
      ctx->up = false;
      break;
    case CMD_HOME:
      ctx->x = 0;
      ctx->y = 0;
      ctx->angle = -90;
      ctx->up = false;
      printf("MoveTo %f %f", ctx->x, ctx->y);
      break;
    case CMD_COLOR:
      printf("Color ");
      if(self->children_count == 3) {
        for(int i=0; i<self->children_count; i++) {
          printf("%f ", ast_eval_expr(self->children[i]));
        }
      } else if(self->children_count == 1) {
        ast_eval_cmd_simple_color(self->children[0]);
      }
      break;
    case CMD_PRINT:
      fprintf(stderr, "%f\n", ast_eval_expr(self->children[0]));
      break;
    default:
      break;
  }
  printf("\n");
}

void ast_eval_cmd_simple_color(const struct ast_node *self)
{
  const char * color = self->u.name;
  if (strcmp(color, "red") == 0) {
    printf("1.0 0.0 0.0");
  } else if (strcmp(color, "green") == 0) {
    printf("0.0 1.0 0.0");
  } else if (strcmp(color, "blue") == 0) {
    printf("0.0 0.0 1.0");
  } else if (strcmp(color, "cyan") == 0) {
    printf("0.0 1.0 1.0");
  } else if (strcmp(color, "yellow") == 0) {
    printf("1.0 0.0 1.0");
  } else if (strcmp(color, "magenta") == 0) {
    printf("1.0 1.0 0.0");
  } else if (strcmp(color, "black") == 0) {
    printf("0.0 0.0 0.0");
  } else if (strcmp(color, "gray") == 0) {
    printf("0.5 0.5 0.5");
  } else if (strcmp(color, "white") == 0) {
    printf("1.0 1.0 1.0");
  }
}

double ast_eval_expr(const struct ast_node *self)
{
  switch (self->kind) {
    case KIND_EXPR_VALUE:
      return self->u.value;
      break;
    case KIND_EXPR_BINOP:
      return ast_eval_expr_op(self);
      break;
    case KIND_EXPR_UNOP:
      return -ast_eval_expr(self->children[0]);
      break;
    case KIND_EXPR_FUNC:
      return ast_eval_expr_func(self);
    default:
      return 0;
      break;
  }
}

double ast_eval_expr_op(const struct ast_node *self)
{
  double x = ast_eval_expr(self->children[0]);
  double y = ast_eval_expr(self->children[1]);
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

double ast_eval_expr_func(const struct ast_node *self)
{
  double x = ast_eval_expr(self->children[0]);
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
      int max = (int)ast_eval_expr(self->children[1]);
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
        printf(" {\n");
        break;
      case KIND_CMD_REPEAT:
        printf("repeat ");
        break;
      case KIND_CMD_SIMPLE:
        switch (self->u.cmd) {
          case CMD_DOWN:
            printf("down");
            break;
          case CMD_UP:
            printf("up");
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
            if(self->children_count==1) {
              print_node(self->children[0]);
            } else {
              print_node(self->children[0]);
              printf(", ");
              print_node(self->children[1]);
              printf(", ");
              print_node(self->children[2]);
            }
            break;
          case CMD_HEADING:
            printf("heading ");
            break;
          case CMD_POSITION:
            comma = true;
            printf("pos ");
            break;
        }
        break;

      case KIND_EXPR_FUNC:
        switch (self->u.func) {
          case FUNC_COS:
            printf("cos(");
            parentheses = true;
            break;
          case FUNC_SIN:
            printf("sin(");
            parentheses = true;
            break;
          case FUNC_TAN:
            printf("tan(");
            parentheses = true;
            break;
          case FUNC_SQRT:
            printf("sqrt(");
            parentheses = true;
            break;
          case FUNC_RANDOM:
            printf("random(");
            parentheses = true;
            comma = true;
            break;
        }
        break;

      case KIND_EXPR_NAME:
        printf("%s", self->u.name);
        break;
      case KIND_EXPR_UNOP:
        printf("%c", self->u.op);
        break;
      case KIND_EXPR_BINOP:
        print_node(self->children[0]);
        printf("%c", self->u.op);
        print_node(self->children[1]);
        break;
      case KIND_EXPR_BLOCK:
        break;
      case KIND_EXPR_VALUE:
        printf("%f", self->u.value);
        break;
    }


    if(self->kind != KIND_EXPR_BINOP && self->u.cmd != CMD_COLOR) {
      for(int i=0; i<self->children_count; ++i) {
        print_node(self->children[i]);

        if(comma == true) {
          printf(", ");
          comma = false;
        }
      }
    }

    if(parentheses == true) {
      printf(") ");
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
