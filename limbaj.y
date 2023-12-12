%{
#include <iostream>
#include <string>
#include <vector>
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

// void globalFunction(int param);

%}

%union {
    int intValue;
    float floatValue;
    char charValue;
    bool boolValue;
    char* string;
}


%token <intValue> INT
%token <floatValue> FLOAT
%token <charValue> CHAR
%token <string> STRING
%token <boolValue> BOOL
%token <string> ID TYPE
%token IF WHILE FOR  
%token SPECIAL_FUNCTION END_USR_TYPES END_GLOBAL_VARS END_GLOBAL_FUNCS
%token CONST USR_TYPE
%token NOT EQ NEQ LT LE GT GE ASSIGN PLUS MINUS MUL DIV MOD AND OR GEQ LEQ

%type <floatValue> expr t f g h i j var

%start program 
%%
// Entry point of the program
program: user_defined_types END_USR_TYPES declarations END_GLOBAL_VARS global_function_definitions END_GLOBAL_FUNCS special_function {printf("The programme is correct!\n");}


user_defined_types: /* epsilon */
                    | user_defined_types user_defined_type
                    ;

// User-defined data types
user_defined_type: USR_TYPE ID '{' usr_type_body '}'
                    ;

usr_type_body: /* epsilon */
            | usr_type_body member
            ;

member: TYPE ID ';'
            | TYPE ID '(' func_param ')' '{' statements '}'
            ;

// Global variables
declarations : decl ';'
                | declarations  decl ';'
                ;

decl: TYPE ID 
        | CONST TYPE ID '=' const_val 
        ;

const_val: INT
            | FLOAT
            | CHAR
            | STRING
            | BOOL
            ;

// Function definitions
global_function_definitions: /* epsilon */
                            | global_function_definitions global_function_definition
                            ;

global_function_definition: TYPE ID '(' func_param ')' '{' statements '}' 
                            ;

func_param: /* epsilon */
            | list_param
            ;

list_param: param
            | list_param ',' param
            ;

param: TYPE ID
        ;




statements: /* epsilon */
            | statements statement
            ;

statement: assignment_statement
            | control_statement
            | function_call_statement
            ;

assignment_statement: left_value ASSIGN expr ';'  {cout << "Expression value: " << $3 << endl;}

left_value: ID
            | array_element_access
            ;

array_element_access: ID '[' expr ']'

control_statement: if_statement
                    | for_statement
                    | while_statement
                    ;

if_statement: IF '(' expr ')' '{' statements '}'
                ;

for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' statements '}'
                ;

while_statement: WHILE '(' expr ')' '{' statements '}'
                ;

function_call_statement: function_call ';'

function_call: ID '(' arguments ')'

arguments: /* epsilon */
            | arg_list
            ;

arg_list: expr 
                | function_call
                | arg_list ',' expr 
                ;



expr: expr AND t { $$ = ($1 && $3); cout << "e && e" << " : " <<$$ <<endl; }
    | expr OR t {($1 || $3); cout << "e || e" << " : " <<$$ <<endl; }
    | t { $$ = $1;}
    ;





t : t EQ f { $$ = ($1 == $3); cout << "e == e" << ": " <<$$ <<endl; }
    | t NEQ f { $$ = ($1 != $3); cout << "e != e" << ": " <<$$ <<endl; }
    | f { $$ = $1;}
    ;
f : f LT g { $$ = ($1 < $3); cout << "e < e" << ": " <<$$ <<endl; }
    | f LE g { $$ = ($1 <= $3); cout << "e <= e" << ": " <<$$ <<endl; }
    | f GT g { $$ = ($1 > $3); cout << "e > e" << ": " <<$$ <<endl; }
    | f GE g { $$ = ($1 >= $3); cout << "e >= e" << ": " <<$$ <<endl; }
    | g { $$ = $1;}
    ;
g : g PLUS h { $$ = ($1 + $3); cout << "e + e" << " : " <<$$ <<endl; }
    | g MINUS h { $$ = ($1 - $3); cout << "e - e" << " : " <<$$ <<endl; }
    | h { $$ = $1;}
    ;
h : h MUL i { $$ = ($1 * $3); cout << "e * e" << " : " <<$$ <<endl; }
    | h DIV i { $$ = ($1 / $3); cout << "e / e" << " : " <<$$ <<endl; }
    | h MOD i { $$ = (float)((int)$1 % (int)$3); cout << "e % e" << " : " <<$$ <<endl; }
    | i { $$ = $1;}
    ;
i : NOT j { $$ = !$2; cout << "!e" << " : " <<$$ <<endl; }
    | j { $$ = $1;}
    ;
j : var { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | INT { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | FLOAT { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | BOOL { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | '(' expr ')' { $$ = $2; cout << "e->(e)" <<$2<< " : " <<$$ <<endl; }
    ;


var : ID {$$ = 0 /* add code to retreive variable value */; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    ;

special_function: SPECIAL_FUNCTION '(' ')' '{' statements '}'
%%

void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
    
}
