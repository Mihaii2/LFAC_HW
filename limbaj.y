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


%token <intValue> _int
%token <floatValue> _float
%token <charValue> _char
%token <string> _string
%token <boolValue> _bool
%token <string> _id _type
%token _if _while _for  
%token _special_function _end_usr_types _end_global_vars _end_global_funcs
%token _const _usr_type
%token _not _eq _neq _lt _le _gt _ge _assign _plus _minus _mul _div _mod _and _or _geq _leq

%type <floatValue> EXPR T F G H I J VAR

%start PROGRAM 
%%
// Entry point of the program
PROGRAM: DECLARATIONS _end_global_vars USER_DEFINED_TYPES _end_usr_types GLOBAL_FUNCTION_DEFINITIONS _end_global_funcs SPECIAL_FUNCTION {printf("The programme is correct!\n");}


USER_DEFINED_TYPES: /* epsilon */
                    | USER_DEFINED_TYPES USER_DEFINED_TYPE
                    ;

// User-defined data types
USER_DEFINED_TYPE: _usr_type _id '{' USR_TYPE_BODY '}'
                    ;

USR_TYPE_BODY: /* epsilon */
            | USR_TYPE_BODY MEMBER
            ;

MEMBER: _type _id ';'
            | _type _id '(' FUNC_PARAM ')' '{' STATEMENTS '}'
            ;

// Global variables
DECLARATIONS : DECL ';'
                | DECLARATIONS  DECL ';'
                ;

DECL: _type _id 
        | _const _type _id '=' CONST_VAL 
        ;

CONST_VAL: _int
            | _float
            | _char
            | _string
            | _bool
            ;

// Function definitions
GLOBAL_FUNCTION_DEFINITIONS: /* epsilon */
                            | GLOBAL_FUNCTION_DEFINITIONS GLOBAL_FUNCTION_DEFINITION
                            ;

GLOBAL_FUNCTION_DEFINITION: _type _id '(' FUNC_PARAM ')' '{' STATEMENTS '}' 
                            ;

FUNC_PARAM: /* epsilon */
            | LIST_PARAM
            ;

LIST_PARAM: PARAM
            | LIST_PARAM ',' PARAM
            ;

PARAM: _type _id
        ;




STATEMENTS: /* epsilon */
            | STATEMENTS STATEMENT
            ;

STATEMENT: ASSIGNMENT_STATEMENT
            | CONTROL_STATEMENT
            | FUNCTION_CALL_STATEMENT
            ;

ASSIGNMENT_STATEMENT: LEFT_VALUE _assign EXPR ';'  {cout << "Expression value: " << $3 << endl;}

LEFT_VALUE: _id
            | ARRAY_ELEMENT_ACCESS
            ;

ARRAY_ELEMENT_ACCESS: _id '[' EXPR ']'

CONTROL_STATEMENT: IF_STATEMENT
                    | FOR_STATEMENT
                    | WHILE_STATEMENT
                    ;

IF_STATEMENT: _if '(' EXPR ')' '{' STATEMENTS '}'
                ;

FOR_STATEMENT: _for '(' ASSIGNMENT_STATEMENT ';' EXPR ';' ASSIGNMENT_STATEMENT ')' '{' STATEMENTS '}'
                ;

WHILE_STATEMENT: _while '(' EXPR ')' '{' STATEMENTS '}'
                ;

FUNCTION_CALL_STATEMENT: FUNCTION_CALL ';'

FUNCTION_CALL: _id '(' ARGUMENTS ')'

ARGUMENTS: /* epsilon */
            | ARG_LIST
            ;

ARG_LIST: EXPR 
                | FUNCTION_CALL
                | ARG_LIST ',' EXPR 
                ;

EXPR: EXPR _and T { $$ = ($1 && $3); cout << "e && e" << " : " <<$$ <<endl; }
    | EXPR _or T {($1 || $3); cout << "e || e" << " : " <<$$ <<endl; }
    | T { $$ = $1;}
    ;
T : T _eq F { $$ = ($1 == $3); cout << "e == e" << ": " <<$$ <<endl; }
    | T _neq F { $$ = ($1 != $3); cout << "e != e" << ": " <<$$ <<endl; }
    | F { $$ = $1;}
    ;
F : F _lt G { $$ = ($1 < $3); cout << "e < e" << ": " <<$$ <<endl; }
    | F _le G { $$ = ($1 <= $3); cout << "e <= e" << ": " <<$$ <<endl; }
    | F _gt G { $$ = ($1 > $3); cout << "e > e" << ": " <<$$ <<endl; }
    | F _ge G { $$ = ($1 >= $3); cout << "e >= e" << ": " <<$$ <<endl; }
    | G { $$ = $1;}
    ;
G : G _plus H { $$ = ($1 + $3); cout << "e + e" << " : " <<$$ <<endl; }
    | G _minus H { $$ = ($1 - $3); cout << "e - e" << " : " <<$$ <<endl; }
    | H { $$ = $1;}
    ;
H : H _mul I { $$ = ($1 * $3); cout << "e * e" << " : " <<$$ <<endl; }
    | H _div I { $$ = ($1 / $3); cout << "e / e" << " : " <<$$ <<endl; }
    | H _mod I { $$ = (float)((int)$1 % (int)$3); cout << "e % e" << " : " <<$$ <<endl; }
    | I { $$ = $1;}
    ;
I : _not J { $$ = !$2; cout << "!e" << " : " <<$$ <<endl; }
    | J { $$ = $1;}
    ;
J : VAR { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | _int { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | _float { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | _bool { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | '(' EXPR ')' { $$ = $2; cout << "e->(e)" <<$2<< " : " <<$$ <<endl; }
    ;


VAR : _id {$$ = 0 /* add code to retreive variable value */; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    ;

SPECIAL_FUNCTION: _special_function '(' ')' '{' STATEMENTS '}'
%%

void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
    
} 
