%{
#include <stdio.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"usr_type" { return USR_TYPE; }
"bool"|"int"|"float"|"char"|"string" {yylval.string = strdup(yytext);return TYPE;}
"==" {return EQ;}
"!=" {return NEQ;}
"<" {return LT;}
"<=" {return LE;}
">" {return GT;}
">=" {return GE;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}
"!" {return NOT;}
"&&" {return AND;}
"||" {return OR;}
"END_USR_TYPES" {return END_USR_TYPES;}
"END_GLOBAL_VARS" {return END_GLOBAL_VARS;}
"END_GLOBAL_FUNCS" {return END_GLOBAL_FUNCS;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"for" {return FOR;}
"clean_code_executer" {return SPECIAL_FUNCTION;}
[0-9]+ {yylval.intValue = atoi(yytext); return INT;}
[0-9]+"."[0-9]+ {yylval.floatValue = atof(yytext); return FLOAT;}
\"[^\"]*\" {yylval.string = strdup(yytext); return STRING;}
"true"|"false" {yylval.string = strdup(yytext); return BOOL;}
"=" {return ASSIGN;}
[a-zA-Z][a-zA-Z0-9]* {yylval.string = strdup(yytext); return ID;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
%%