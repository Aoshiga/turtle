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

/**
 * Create ast_node expressions
 */
struct ast_node *make_expr_name(char *name)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->children_count = 0;
  node->u.name = name;
  return node;
}

struct ast_node *make_expr_value(double value)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->children_count = 0;
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

/**
 * Create ast_node simple commands
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

/**
 * Create ast_node of other commands
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

struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SET;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = expr;
  return node;
}

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_PROC;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = expr;
  return node;
}

struct ast_node *make_cmd_call(struct ast_node *name)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_CALL;
  node->children_count = 1;
  node->children[0] = name;
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

/**
 * Add a new variable to the programm at the end of the variable list
 */
void variable_add(struct variable *self, char* name, double value)
{
  // Create a new variable
  struct variable_node *vn = malloc(sizeof(struct variable_node));
  if(vn == NULL)
  {
    printf("Allocation error");
    return;
  }

  vn->value = value;
  vn->name = name;
  vn->next = NULL;

  if(self->first == NULL) { self->first = vn; }
  else {
    struct variable_node *stepNext = self->first;
    while (stepNext->next != NULL)
    {
      if(strcmp(stepNext->name, name) == 0) {
        fprintf(stderr, "Redefinition of %s variable\n", name);
        exit(1);
      }
      stepNext = stepNext->next;
    }

    // Last node (unaccessible in the while loop)
    if(strcmp(stepNext->name, name) == 0) {
      fprintf(stderr, "Redefinition of %s variable\n", name);
      exit(1);
    }
    stepNext->next = vn;
  }
}

/**
 * Add a new variable to the programm at the end of the variable list
 */
void procedure_add(struct procedure *self, char* name, struct ast_node *unit)
{
  // Throw an error if an another procedure is define inside the self procedure
  if(unit->kind == KIND_CMD_PROC) {
    fprintf(stderr, "Procedures cannot be defined in another procedure\n");
    exit(1);
  } else if (unit->kind == KIND_CMD_BLOCK) {
    struct ast_node *stepNext = unit->children[0];
    while(stepNext != NULL) {
      if(stepNext->kind == KIND_CMD_PROC) {
        fprintf(stderr, "Procedures cannot be defined in another procedure\n");
        exit(1);
      }
      stepNext = stepNext->next;
    }
  }

  // Create a new procedure
  struct procedure_node *pn = malloc(sizeof(struct procedure_node));
  if(pn == NULL)
  {
    printf("Allocation error");
    return;
  }

  pn->cmd = unit;
  pn->name = name;
  pn->next = NULL;

  if(self->first == NULL) { self->first = pn; }
  else
  {
    struct procedure_node *stepNext = self->first;
    while (stepNext->next != NULL)
    {
      if(strcmp(stepNext->name, name) == 0) {
        fprintf(stderr, "Redefinition of %s procedure\n", name);
        exit(1);
      }
      stepNext = stepNext->next;
    }

    // Last node (unaccessible in the while loop)
    if(strcmp(stepNext->name, name) == 0) {
      fprintf(stderr, "Redefinition of %s procedure\n", name);
      exit(1);
    }
    stepNext->next = pn;
  }
}

/**
 * initial context
 */
void context_create(struct context *self) {
  self->x = 0;
  self->y = 0;
  self->angle = -90;
  self->up = false;

  self->var.first = NULL;
  variable_add(&self->var, "PI", PI);
  variable_add(&self->var, "SQRT2", SQRT2);
  variable_add(&self->var, "SQRT3", SQRT3);

  self->proc.first = NULL;
}

/**
 * Evaluate function : used to eval a turtle program
 */

void ast_eval(const struct ast *self, struct context *ctx) {
  if(self!=NULL)
  {
    struct ast_node * root = self->unit;
    ast_eval_cmd(root, ctx);
  }
}

// Evaluation of the commands
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
        loop = floor(ast_eval_expr(self->children[0], ctx));
        for(int i=0; i<loop; ++i) {
          ast_eval_cmd(self->children[1], ctx);
        }
        break;
      case KIND_CMD_SET:
        variable_add(&ctx->var, self->children[0]->u.name, ast_eval_expr(self->children[1], ctx));
        break;
      case KIND_CMD_PROC:
        procedure_add(&ctx->proc, self->children[0]->u.name, self->children[1]);
        break;
      case KIND_CMD_CALL:
        ast_eval_cmd_call(self->children[0], ctx);
        break;
      default:
        break;
    }

    ast_eval_cmd(self->next, ctx);
  }
}

// Evaluation of the commands call
void ast_eval_cmd_call(const struct ast_node *self, struct context *ctx)
{
  struct procedure_node *stepNext = ctx->proc.first;
  while (stepNext->next != NULL)
  {
    if(strcmp(self->u.name, stepNext->name) == 0) {
      ast_eval_cmd(stepNext->cmd, ctx);
      return;
    }
    stepNext = stepNext->next;
  }

  // The last element of the list
  if(strcmp(self->u.name, stepNext->name) == 0) {
    ast_eval_cmd(stepNext->cmd, ctx);
    return;
  } else {
    fprintf(stderr, "Undefined procedure %s\n", self->u.name);
    exit(1);
  }
}

// Evaluation of the simple commands
void ast_eval_cmd_simple(const struct ast_node *self, struct context *ctx)
{
  switch (self->u.cmd) {
    case CMD_FORWARD:
      ctx->x += cos(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0], ctx);
      ctx->y += sin(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0], ctx);
      if(!ctx->up){
        printf("LineTo %f %f", ctx->x, ctx->y);
      } else {
        printf("MoveTo %f %f", ctx->x, ctx->y);
      }
      break;
    case CMD_BACKWARD:
      ctx->x -= cos(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0], ctx);
      ctx->y -= sin(ctx->angle * PI / 180.0)*ast_eval_expr(self->children[0], ctx);
      if(!ctx->up){
        printf("LineTo %f %f", ctx->x, ctx->y);
      } else {
        printf("MoveTo %f %f", ctx->x, ctx->y);
      }
      break;
    case CMD_POSITION:
      ctx->x = ast_eval_expr(self->children[0], ctx);
      ctx->y = ast_eval_expr(self->children[1], ctx);
      printf("MoveTo %f %f", ctx->x, ctx->y);
      break;
    case CMD_RIGHT:
      ctx->angle += ast_eval_expr(self->children[0], ctx);
      break;
    case CMD_LEFT:
      ctx->angle -= ast_eval_expr(self->children[0], ctx);
      break;
    case CMD_HEADING:
      ctx->angle = ast_eval_expr(self->children[0], ctx)-90; //-90 cause 0 must to be the north -- in turtle-viewer, the north is -90
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
          printf("%f ", ast_eval_expr(self->children[i], ctx));
        }
      } else if(self->children_count == 1) {
        ast_eval_cmd_simple_color(self->children[0]);
      }
      break;
    case CMD_PRINT:
      fprintf(stderr, "%f\n", ast_eval_expr(self->children[0], ctx));
      break;
    default:
      break;
  }
  printf("\n");
}

// Evaluation of the simple color called with a keyword
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

/**
 * Evaluation of expressions
 * Return a double equal to the value of the current expressions
 */
double ast_eval_expr(const struct ast_node *self, struct context *ctx)
{
  switch (self->kind) {
    case KIND_EXPR_VALUE:
      return self->u.value;
      break;
    case KIND_EXPR_BINOP:
      return ast_eval_expr_op(self, ctx);
      break;
    case KIND_EXPR_UNOP:
      return -ast_eval_expr(self->children[0], ctx);
      break;
    case KIND_EXPR_FUNC:
      return ast_eval_expr_func(self, ctx);
      break;
    case KIND_EXPR_NAME:
      return ast_eval_expr_name(self, ctx);
      break;
    default:
      return 0;
      break;
  }
}

// Evaluation of an expressions of type name (= variable)
double ast_eval_expr_name(const struct ast_node *self, struct context *ctx)
{
  struct variable_node *stepNext = ctx->var.first;
  while (stepNext->next != NULL)
  {
    if(strcmp(self->u.name, stepNext->name) == 0) {
      return stepNext->value;
    }
    stepNext = stepNext->next;
  }

  //The last element of the list
  if(strcmp(self->u.name, stepNext->name) == 0) {
    return stepNext->value;
  } else {
    fprintf(stderr, "Undefined variable %s\n", self->u.name);
    exit(1);
  }
  return 0;
}

// Evaluation of operations
double ast_eval_expr_op(const struct ast_node *self, struct context *ctx)
{
  double x = ast_eval_expr(self->children[0], ctx);
  double y = ast_eval_expr(self->children[1], ctx);
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
        fprintf(stderr, "Division by zero is forbiden\n");
        exit(1);
      }
      return x/y;
      break;
    case '^' :
      return pow(x,y);
      break;
    default :
      return 0;
      break;
  }
}

// Evaluation of functions
double ast_eval_expr_func(const struct ast_node *self, struct context *ctx)
{
  double x = ast_eval_expr(self->children[0], ctx);
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
      if(x < 0) {
        fprintf(stderr, "Sqrt of negative number is forbiden\n");
        exit(1);
      }
      return sqrt(x);;
      break;
    case FUNC_RANDOM :
      {int min = (int)x;
      int max = (int)ast_eval_expr(self->children[1], ctx);
      if(min>max){
        fprintf(stderr, "random x y with x<y is not respected: %d >= %d\n", min, max);
        exit(1);
      }
      return (rand()%(max-min+1)+min);}
      break;
    default :
      return 0;
      break;
  }
}


/*
 * Print the turtle program in the console
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

    // Browse the children of each node eand print it
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

    // Put a linebrak only at the end of a command
    if(self->kind == KIND_CMD_SET || self->kind == KIND_CMD_CALL || self->kind == KIND_CMD_PROC || self->kind == KIND_CMD_BLOCK || self->kind == KIND_CMD_REPEAT || self->kind == KIND_CMD_SIMPLE) {
      printf("\n");
    }

    print_node(self->next);
  }
}
