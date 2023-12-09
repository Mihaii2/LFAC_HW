%{
#include <stdio.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"usr_type" { return _usr_type; }
"bool"|"int"|"float"|"char"|"string" {yylval.string = strdup(yytext);return _type;}
"==" {return _eq;}
"!=" {return _neq;}
"<" {return _lt;}
"<=" {return _leq;}
">" {return _gt;}
">=" {return _geq;}
"+" {return _plus;}
"-" {return _minus;}
"*" {return _mul;}
"/" {return _div;}
"%" {return _mod;}
"!" {return _not;}
"&&" {return _and;}
"||" {return _or;}
"END_USR_TYPES" {return _end_usr_types;}
"END_GLOBAL_VARS" {return _end_global_vars;}
"END_GLOBAL_FUNCS" {return _end_global_funcs;}
"if" {return _if;}
"while" {return _while;}
"for" {return _for;}
"clean_code_executer" {return _special_function;}
[0-9]+ {yylval.intValue = atoi(yytext); return _int;}
[0-9]+"."[0-9]+ {yylval.floatValue = atof(yytext); return _float;}
\'[^\']\' {yylval.charValue = yytext[1]; return _char;}
\"[^\"]*\" {yylval.string = strdup(yytext); return _string;}
"true"|"false" {yylval.string = strdup(yytext); return _bool;}
"=" {return _assign;}
[a-zA-Z][a-zA-Z0-9]* {yylval.string = strdup(yytext); return _id;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
%%