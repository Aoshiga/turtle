%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
QUIT  'quit'
COMMENT "#".*


%%


"forward"             { return KW_FORWARD; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
^{QUIT}$              { yylval.quit = strdup(yytext); return QUIT;}
<<<<<<< HEAD
{COMMENT}             { printf("%s\n", yytext); }
=======
{COMMENT}             { printf("%s\n",yytext);}
>>>>>>> a1fd418c52173628adee214b0688408f20ff6522

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
