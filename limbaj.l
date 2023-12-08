%{
#include <stdio.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"begin_progr" {return BGIN;}
"end_progr" {return END;}
"const" {yylval.string = strdup(yytext); return CONST;}
"bool"|"int"|"float"|"char"|"string" {yylval.string = strdup(yytext);return TYPE;}
"struct" {yylval.string = strdup(yytext);return STRUCT;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
"=" {return ASSIGN;}
[0-9]+ {return NR;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
%%