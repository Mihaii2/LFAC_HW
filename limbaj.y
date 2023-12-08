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
%token IF ELSE WHILE FOR  
%token SPECIAL_FUNCTION END_USR_TYPES END_GLOBAL_VARS END_GLOBAL_FUNCS
%token CONST CLASS
%token NOT EQ NEQ LT LE GT GE ASSIGN PLUS MINUS MUL DIV 0 MOD AND OR

%start program 
%%
// Entry point of the program
program: user_defined_types END_USR_TYPES declarations END_GLOBAL_VARS global_function_definitions END_GLOBAL_FUNCS special_function {printf("The programme is correct!\n");}


user_defined_types: /* epsilon */
                    | user_defined_types user_defined_type
                    ;

// User-defined data types
user_defined_type: CLASS ID '{' class_body '}' {
    printf("User-defined type: %s\n", $2);
    // Code to handle user-defined types
    // You can store the type information in a symbol table or generate C++ code for the type
}

class_body: /* epsilon */
            | class_body class_member
            ;

class_member: TYPE ID ';'
            | TYPE ID '(' list_param ')' '{' statements '}'
            ;

// Global variables
declarations : decl ';'
                | declarations  decl ';'
                ;

decl: TYPE ID {
    printf("Variable: %s, name: %s\n", $1, $2);
    // Code to handle global variable declarations
    // You can store the variable information in a symbol table or generate C++ code for the variable
    // Access the variable using $$ = $2;
    }
        | CONST TYPE ID '=' CONST_VAL {
            // Code to handle global constant declarations
            // You can store the constant information in a symbol table or generate C++ code for the constant
            // Access the constant using $$ = $4;
        }

CONST_VAL: INT
            | FLOAT
            | CHAR
            | STRING
            | BOOL
            ;

// Function definitions
global_function_definitions: /* epsilon */
                            | global_function_definitions global_function_definition
                            ;

global_function_definition: TYPE ID '(' list_param ')' '{' statements '}' {
    // Code to handle function definitions
    // You can store the function information in a symbol table or generate C++ code for the function
    // Access the function using $$ = $2;
}

list_param: /* epsilon */
            | list_param param
            ;

param: TYPE ID {
    // Code to handle function parameters
    // You can store the parameter information in a symbol table or generate C++ code for the parameter
}




statements: /* epsilon */
            | statements statement
            ;

statement: assignment_statement
            | control_statement
            | function_call_statement
            ;

assignment_statement: left_value ASSIGN expr ';' {
    // Code to handle assignment statements
    // You can generate C++ code for the assignment
}

left_value: ID
            | array_element_access
            ;

array_element_access: ID '[' expr ']'

control_statement: if_statement
                    | for_statement
                    | while_statement
                    ;

if_statement: IF '(' expr ')' '{' statements '}' {
    // Code to handle if statements
    // You can generate C++ code for the if statement
}

for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' statements '}' {
    // Code to handle for statements
    // You can generate C++ code for the for statement
}

while_statement: WHILE '(' expr ')' '{' statements '}' {
    // Code to handle while statements
    // You can generate C++ code for the while statement
}

function_call_statement: function_call ';'

function_call: ID '(' arguments ')'

arguments: /* epsilon */
            | arguments_list
            ;

arguments_list: expr
                | arguments_list ',' expr
                ;

expr: NOT T
    | T
    ;
T : T EQ F
    | T NEQ F
    | F
    ;
F : F LT G
    | F LE G
    | F GT G
    | F GE G
    | G
    ;
G : G PLUS H
    | G MINUS H
    | H
    ;
H : H MUL I
    | H DIV I
    | H MOD I
    | I
    ;
I : I AND J
    | I OR J
    | J
    ;
J : ID
    | INT
    | FLOAT
    | CHAR
    | STRING
    | BOOL
    | '(' expr ')'
    ;


special_function: SPECIAL_FUNCTION '(' ')' '{' statements '}'
%%

// // Function to evaluate expressions
// void Eval(arg) {
//     // Code to evaluate expressions
//     // You can generate C++ code for evaluating the expression
// }

// // Function to get the type of an expression
// void TypeOf(arg) {
//     // Code to get the type of an expression
//     // You can generate C++ code for getting the type
// }

// // Function to handle global function calls
// void globalFunction(int param) {
//     // Code to handle global function calls
//     // You can generate C++ code for the function call
// }

void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
    
} 
