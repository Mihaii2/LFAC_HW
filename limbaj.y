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

// class VarInfo {
//     string type
//     string name;
//     string scope 
//     Value val;
// }

// class FunctionInfo {
//     string type;
//     string name;
//     string scope;
//     ListParam params;

// }

// class ListParam {
//     vector<VarInfo> params;
// }

// class IdList {
//     vector<string> vars;

//     public:
//         bool existsVar(const char* s);
//         void addVar(const char* s);
//         //...
// }   

%}

%union {
    int intValue;
    float floatValue;
    char charValue;
    bool boolValue;
    char* string;
    //class VarInfo * PtrVarInfo;
    //class ListParam * PtrListParam;
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
//%type<PtrListParam> list_param


%type <intValue> expr

%left AND OR
%left LT LE GT GE EQ NEQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT

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
        | TYPE ID ASSIGN const_val
        | CONST TYPE ID ASSIGN const_val
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
            | decl ';'
            | control_statement
            | function_call_statement
            ;

assignment_statement: left_value ASSIGN expr ';'
                        ;

left_value: ID
            | array_element_access
            ;

array_element_access: ID '[' expr ']'

control_statement: if_statement
                    | for_statement
                    | while_statement
                    ;

if_statement: IF '(' expr ')' '{' statements '}'
                | IF '(' e_bool ')' '{' statements '}'
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

expr: expr PLUS expr
        | expr MINUS expr
        | expr MUL expr
        | expr DIV expr
        | expr MOD expr
        | var  
        | INT
        | '(' expr ')'
        ;

var : ID
    ;

e_bool: expr EQ expr
        | expr NEQ expr
        | expr LT expr
        | expr LE expr
        | expr GT expr
        | expr GE expr
        | e_bool AND e_bool
        | e_bool OR e_bool
        | '(' e_bool ')'
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
