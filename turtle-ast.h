#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

// simple commands
enum ast_cmd {
  CMD_UP,
  CMD_DOWN,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_HOME,
  CMD_COLOR,
  CMD_PRINT,
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_RANDOM,
  FUNC_SIN,
  FUNC_SQRT,
  FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,

  KIND_EXPR_FUNC,
  KIND_EXPR_VALUE,
  KIND_EXPR_UNOP,
  KIND_EXPR_BINOP,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // kind == KIND_CMD_SIMPLE
    double value;       // kind == KIND_EXPR_VALUE, for literals
    char op;            // kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
    char *name;         // kind == KIND_EXPR_NAME, the name of procedures and variables
    enum ast_func func; // kind == KIND_EXPR_FUNC, a function
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};

// Constructor for operators
struct ast_node *make_expr_value(double value);
struct ast_node *make_expr_name(char *name);
struct ast_node *make_expr_func(enum ast_func func, struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_expr_unary_op(char op, struct ast_node *expr);
struct ast_node *make_expr_binary_op(char op, struct ast_node *expr1, struct ast_node *expr2);

// Constructor of simple commands
struct ast_node *make_cmd_up();
struct ast_node *make_cmd_down();
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_home();
struct ast_node *make_cmd_color_from_keyword(struct ast_node *expr);
struct ast_node *make_cmd_color_from_expr(struct ast_node *red, struct ast_node *green, struct ast_node *blue);
struct ast_node *make_cmd_print(struct ast_node *expr);
// Construct other commands
struct ast_node *make_cmd_block(struct ast_node *cmd);
struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd);
struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr);
struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *expr);
struct ast_node *make_cmd_call(struct ast_node *name);

// Constructor of commands quit
void *make_cmd_quit();

// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};
//Helper functions
void freeNode(struct ast_node *self);

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);

// List used to save the variable define by the user
struct variable {
  struct variable_node *first;
};

struct variable_node {
  char* name;
  double value;
  struct variable_node *next;
};

// List used to save the procedure define by the user
struct procedure {
  struct procedure_node *first;
};

struct procedure_node {
  char* name;
  struct ast_node *cmd;
  struct procedure_node *next;
};

// Add varable/procedure to the list of variable/procedure
void variable_add(struct variable *self, char* name, double value);
void procedure_add(struct procedure *self, char* name, struct ast_node *unit);

// the execution context
struct context {
  double x;
  double y;
  double angle;
  bool up;

  //we add the following element:
  struct variable var;
  struct procedure proc;
};

// create an initial context
void context_create(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);
void print_node(struct ast_node *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);
void ast_eval_cmd(const struct ast_node *self, struct context *ctx);
void ast_eval_cmd_simple(const struct ast_node *self, struct context *ctx);
void ast_eval_cmd_simple_color(const struct ast_node *self);
void ast_eval_cmd_call(const struct ast_node *self, struct context *ctx);

// evaluate expressions
double ast_eval_expr(const struct ast_node *self, struct context *ctx);
double ast_eval_expr_op(const struct ast_node *self, struct context *ctx);
double ast_eval_expr_func(const struct ast_node *self, struct context *ctx);
double ast_eval_expr_name(const struct ast_node *self, struct context *ctx);


#endif /* TURTLE_AST_H */
