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
"{"                   { return '{'; }
"}"                   { return '}'; }

"sin"                 { return SIN; }
"cos"                 { return COS; }
"tan"                 { return TAN; }
"sqrt"                { return SQRT; }
"random"              { return RANDOM; }

"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"right"|"rt"          { return KW_RIGHT; }
"left"|"lt"           { return KW_LEFT; }
"heading"|"hd"        { return KW_HEADING; }
"forward"|"fw"        { return KW_FORWARD; }
"backward"|"bw"       { return KW_BACKWARD; }
"position"|"pos"      { return KW_POSITION; }
"home"                { return KW_HOME; }
"color"               { return KW_COLOR; }
"print"               { return KW_PRINT; }

"repeat"              { return REPEAT; }

{DOUBLE}              { yylval.value = strtod(yytext, NULL); return VALUE; }
{COLOR_VALUE}         { yylval.name = strdup(yytext); return NAME; }
{ID}                  { yylval.name = strdup(yytext); return NAME; }
{COMMENT}             { printf("%s\n", yytext); }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
/* {DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; } */
/*^{QUIT}               { yylval.quit = strtod(yytext, NULL); return QUIT;}*/
