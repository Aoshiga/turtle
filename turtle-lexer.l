%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT           [0-9]
ID              [A-Z][A-Z0-9]*
INT             [1-9]{DIGIT}*|[0]
DOUBLE          ({DIGIT}*"."{DIGIT}+)|({INT}"e-"{DIGIT})|{INT}
QUIT            "quit"
COMMENT         #.*
COLOR_VALUE     "red"|"green"|"blue"|"cyan"|"magenta"|"yellow"|"black"|"gray"|"white"

%%

"^"                   { return '^'; }
"+"                   { return '+'; }
"-"                   { return '-'; }
"*"                   { return '*'; }
"/"                   { return '/'; }
"("                   { return '('; }
")"                   { return ')'; }
","                   { return ','; }
"\n"                  { return '\n'; }

"sin"                 { return SIN; }
"cos"                 { return COS; }
"tan"                 { return TAN; }
"sqrt"                { return SQRT; }
"random"              { return RANDOM; }

"color"               { return COLOR; }
"forward"             { return KW_FORWARD; }

{DOUBLE}              { yylval.value = strtod(yytext, NULL); return VALUE; }
{COLOR_VALUE}         { yylval.name = strdup(yytext); return NAME; }
{ID}                  { yylval.name = strdup(yytext); return NAME; }
^{QUIT}               { yylval.quit = strtod(yytext, NULL); return QUIT;}
{COMMENT}             { printf("%s\n", yytext); }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
/* {DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; } */
