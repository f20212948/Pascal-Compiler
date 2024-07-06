%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

extern FILE *yyin;
%}
ID [a-zA-Z][a-zA-Z0-9_]*
ANUM [1-9][0-9]*

%%

[Pp][Rr][Oo][Gg][Rr][Aa][Mm][ ]{ID} {return PROG_ID;}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]  {  return INT;}
[Rr][Ee][Aa][Ll] { return REAL;}
[Bb][Oo][Oo][Ll][Ee][Aa][Nn] { return BOOL;}
[Cc][Hh][Aa][Rr] { return CHAR;}
[Vv][Aa][Rr] { return VAR;}
[Tt][Oo] { return TO;}
[Dd][Oo][Ww][Nn][Tt][Oo] { return DOWNTO;}
[Ii][Ff] {return IF;}
[Ee][Ll][Ss][Ee] { return ELSE;}
[Ww][Hh][Ii][Ll][Ee] { return WHILE;}
[Ff][Oo][Rr] { return FOR;}
[Tt][Hh][Ee][Nn] { return THEN;}
[Dd][Oo] { return DO;}
[Aa][Rr][Rr][Aa][Yy] { return ARRAY;}
[Oo][Ff] { return OF;}
[Aa][Nn][Dd] { return AND;}
[Oo][Rr] { return OR;}
[Nn][Oo][Tt] { return NOT;}
[Bb][Ee][Gg][Ii][Nn] { return BEG;}
[Ee][Nn][Dd] { return END;}
[Rr][Ee][Aa][Dd] { return READ;}
[Ww][Rr][Ii][Tt][Ee] { return WRITE;}
{ID} {yylval.sval = strdup(yytext); return ID;}
[0-9]+ {yylval.ival = atoi(yytext); return NUM;}
[0-9]+\.[0-9]+ {yylval.rval = atof(yytext); return REALNUM;}
\/\/.* {}
" " {}
\t {}
\n {}
\[{ANUM}\.{ANUM}\] {yylval.sval = strdup(yytext); return RANGE;}
\".*\" {yylval.sval = strdup(yytext); return STRING;}
\+ { return PLUS;}
\- { return MINUS;}
\* { return MULTIPLY;}
\/ { return DIVIDE;}
"%" { return MOD;}
\= { return EQUAL;}
":=" { return ASSIGN;}
\< { return LT;}
\> { return GT;}
\<\= { return LTE;}
\>\= { return GTE;}
\<\> { return NE;}
\; { return SEMICOLON;}
\: { return COLON;}
\, { return COMMA;}
\. { return DOT;}
\( { return LP;}
\) { return RP;}
\[ { return LB;}
\] { return RB;}
. {}


%%



