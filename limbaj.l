%{
#include <stdio.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"usr_type" { return USR_TYPE; }
"bool"|"int"|"float"|"char"|"string" {yylval.string = strdup(yytext);return TYPE;}
"const" {return CONST;}
"==" {return EQ;}
"!=" {return NEQ;}
"<" {return LT;}
"<=" {return LEQ;}
">" {return GT;}
">=" {return GEQ;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}
"!" {return NOT;}
"&&" {return AND;}
"||" {return OR;}
"#END_USR_TYPE_VARS" {return END_USR_TYPE_VARS;}
"#END_USR_TYPES" {return END_USR_TYPES;}
"#END_GLOBAL_VARS" {return END_GLOBAL_VARS;}
"#END_GLOBAL_FUNCS" {return END_GLOBAL_FUNCS;}
"if" {return IF;}
"while" {return WHILE;}
"for" {return FOR;}
"clean_code_executer" {return SPECIAL_FUNCTION;}
[0-9]+ {yylval.intValue = atoi(yytext); return INT;}
[0-9]+"."[0-9]+ {yylval.floatValue = atof(yytext); return FLOAT;}
\'[^\']\' {yylval.charValue = yytext[1]; return CHAR;}
\"[^\"]*\" {yylval.string = strdup(yytext); return STRING;}
"true"|"false" {
    if(yytext[0] == 't') {
        yylval.boolValue = 1;
    } else {
        yylval.boolValue = 0;
    
    }
    return BOOL;
}
"=" {return ASSIGN;}
[a-zA-Z_][a-zA-Z0-9_]* {yylval.string = strdup(yytext); return ID;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
%%